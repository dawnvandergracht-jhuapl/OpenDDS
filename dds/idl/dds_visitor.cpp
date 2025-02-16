/*
 *
 *
 * Distributed under the OpenDDS License.
 * See: http://www.opendds.org/license.html
 */

#include "ast_argument.h"
#include "ast_attribute.h"
#include "ast_component_fwd.h"
#include "ast_enum.h"
#include "ast_enum_val.h"
#include "ast_eventtype.h"
#include "ast_eventtype_fwd.h"
#include "ast_exception.h"
#include "ast_factory.h"
#include "ast_home.h"
#include "ast_interface.h"
#include "ast_module.h"
#include "ast_native.h"
#include "ast_operation.h"
#include "ast_predefined_type.h"
#include "ast_root.h"
#include "ast_sequence.h"
#include "ast_structure.h"
#include "ast_union.h"
#include "ast_valuetype.h"
#include "ast_valuetype_fwd.h"
#include "utl_identifier.h"
#include "utl_string.h"
#include "utl_exceptlist.h"
#include "utl_err.h"
#include "nr_extern.h"

#include "dds_visitor.h"
#include "metaclass_generator.h"
#include "ts_generator.h"
#include "marshal_generator.h"
#include "keys_generator.h"
#include "itl_generator.h"
#include "v8_generator.h"
#include "rapidjson_generator.h"
#include "langmap_generator.h"
#include "topic_keys.h"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

namespace {

  marshal_generator mar_gen_;
  keys_generator key_gen_;
  ts_generator ts_gen_;
  metaclass_generator mc_gen_;
  itl_generator itl_gen_;
  v8_generator v8_gen_;
  rapidjson_generator rj_gen_;
  langmap_generator lm_gen_;

  template <typename T>
  void scope2vector(vector<T*>& v, UTL_Scope* s, AST_Decl::NodeType nt)
  {
    UTL_ScopeActiveIterator it(s, UTL_Scope::IK_decls);

    for (; !it.is_done(); it.next()) {
      AST_Decl* item = it.item();

      if (item->node_type() == nt) {
        v.push_back(T::narrow_from_decl(item));
      }
    }
  }

  bool field_check_anon(AST_Field* f)
  {
    AST_Decl::NodeType nt = f->field_type()->node_type();
    if (nt == AST_Decl::NT_array || nt == AST_Decl::NT_sequence) {
      idl_global->err()->misc_error("field has an anonymous type.", f);
      return false;
    }
    return true;
  }
} // namespace

dds_visitor::dds_visitor(AST_Decl* scope, bool java_ts_only)
  : scope_(scope), error_(false), java_ts_only_(java_ts_only)
{
  if (!be_global->no_default_gen()) {
    gen_target_.add_generator(&mar_gen_);
    gen_target_.add_generator(&key_gen_);
    gen_target_.add_generator(&ts_gen_);
    gen_target_.add_generator(&mc_gen_);
  }
  if (be_global->itl()) {
    gen_target_.add_generator(&itl_gen_);
  }
  if (be_global->v8()) {
    gen_target_.add_generator(&v8_gen_);
  }
  if (be_global->rapidjson()) {
    gen_target_.add_generator(&rj_gen_);
  }
  if (be_global->language_mapping() != BE_GlobalData::LANGMAP_NONE) {
    gen_target_.add_generator(&lm_gen_);
    lm_gen_.init();
  }
}

dds_visitor::~dds_visitor()
{
}

//visit_* functions

int
dds_visitor::visit_root(AST_Root* node)
{
  error_ = false;

  gen_target_.gen_prologue();
  if (this->visit_scope(node) == -1) {
    ACE_ERROR_RETURN((LM_ERROR,
                      ACE_TEXT("(%N:%l) dds_visitor::visit_root -")
                      ACE_TEXT(" visit_scope failed\n")), -1);
  }
  gen_target_.gen_epilogue();

  return (error_) ? -1 : 0;
}

int
dds_visitor::visit_scope(UTL_Scope* node)
{
  if (node->nmembers() > 0) {
    UTL_ScopeActiveIterator si(node, UTL_Scope::IK_decls);
    AST_Decl* d = 0;

    while (!si.is_done()) {
      d = si.item();

      if (d == 0) {
        ACE_ERROR_RETURN((LM_ERROR,
                          ACE_TEXT("(%N:%l) dds_visitor::visit_")
                          ACE_TEXT("scope - bad node in this scope\n")), -1);
      }

      if (d->node_type() == AST_Decl::NT_pre_defined) {
        si.next();
        continue;
      }

      if (d->ast_accept(this) == -1) {
        ACE_ERROR_RETURN((LM_ERROR,
                          ACE_TEXT("(%N:%l) dds_visitor::visit_")
                          ACE_TEXT("scope - failed to accept visitor\n")), -1);
      }

      si.next();
    }
  }

  return 0;
}

int
dds_visitor::visit_module(AST_Module* node)
{
  const char* name = node->local_name()->get_string();

  BE_Comment_Guard g("MODULE", name);

  ACE_UNUSED_ARG(g);

  if (this->visit_scope(node) == -1) {
    ACE_ERROR_RETURN((LM_ERROR,
                      ACE_TEXT("(%N:%l) dds_visitor::visit_module -")
                      ACE_TEXT(" visit_scope failed\n")), -1);
  }

  return 0;
}

int
dds_visitor::visit_interface(AST_Interface* node)
{
  const char* name = node->local_name()->get_string();

  BE_Comment_Guard g("INTERFACE", name);

  ACE_UNUSED_ARG(g);

  vector<AST_Interface*> inherits(node->n_inherits());
  for (int i = 0; i < node->n_inherits(); ++i) {
    inherits[i] = dynamic_cast<AST_Interface*>(node->inherits()[i]);
  }

  vector<AST_Interface*> inherits_flat(node->inherits_flat(),
                                       node->inherits_flat()
                                       + node->n_inherits_flat());

  vector<AST_Attribute*> attrs;

  scope2vector(attrs, node, AST_Decl::NT_attr);

  vector<AST_Operation*> ops;

  scope2vector(ops, node, AST_Decl::NT_op);

  if (!java_ts_only_) {
    error_ |= !gen_target_.gen_interf(node, node->name(), node->is_local(),
                                      inherits, inherits_flat, attrs, ops,
                                      node->repoID());
  }

  if (this->visit_scope(node) == -1) {
    ACE_ERROR_RETURN((LM_ERROR,
                      ACE_TEXT("(%N:%l) dds_visitor::visit_interface ")
                      ACE_TEXT("- visit_scope failed\n")), -1);
  }

  return 0;
}

int
dds_visitor::visit_structure(AST_Structure* node)
{
  const char* name = node->local_name()->get_string();

  BE_Comment_Guard g("STRUCT", name);
  ACE_UNUSED_ARG(g);

  // Check That Sample Keys Are Valid
  try {
    TopicKeys(node).count();
  } catch (TopicKeys::Error& error) {
    idl_global->err()->misc_error(error.what(), error.node());
    return -1;
  }

  size_t nfields = node->nfields();
  vector<AST_Field*> fields;
  fields.reserve(nfields);
  for (CORBA::ULong i = 0; i < nfields; ++i) {
    AST_Field** f;
    node->field(f, i);
    if (!field_check_anon(*f)) {
      error_ = true;
      return -1;
    }
    fields.push_back(*f);
  }

  if (!java_ts_only_) {
    error_ |= !gen_target_.gen_struct(node, node->name(), fields,
                                      node->size_type(), node->repoID());
  }

  if (be_global->java()) {
    java_ts_generator::generate(node);
  }

  return 0;
}

int
dds_visitor::visit_exception(AST_Exception* node)
{
  if (node->imported()) {
    return 0;
  }

  const char* name = node->local_name()->get_string();

  BE_Comment_Guard g("EXCEPTION", name);

  ACE_UNUSED_ARG(g);

  return 0;
}

int
dds_visitor::visit_typedef(AST_Typedef* node)
{
  const char* name = node->local_name()->get_string();

  BE_Comment_Guard g("TYPEDEF", name);

  ACE_UNUSED_ARG(g);

  if (!java_ts_only_) {
    error_ |= !gen_target_.gen_typedef(node, node->name(), node->base_type(),
                                       node->repoID());
  }

  return 0;
}

int
dds_visitor::visit_enum(AST_Enum* node)
{
  const char* name = node->local_name()->get_string();

  BE_Comment_Guard g("ENUM", name);

  ACE_UNUSED_ARG(g);

  vector<AST_EnumVal*> contents;

  scope2vector(contents, node, AST_Decl::NT_enum_val);

  if (!java_ts_only_) {
    error_ |= !gen_target_.gen_enum(node, node->name(), contents, node->repoID());
  }

  return 0;
}

int
dds_visitor::visit_interface_fwd(AST_InterfaceFwd* node)
{
  const char* name = node->local_name()->get_string();
  BE_Comment_Guard g("INTERFACE-FWD", name);
  ACE_UNUSED_ARG(g);

  if (!java_ts_only_) {
    error_ |= !gen_target_.gen_interf_fwd(node->name());
  }

  return 0;
}

int
dds_visitor::visit_structure_fwd(AST_StructureFwd* node)
{
  const char* name = node->local_name()->get_string();
  BE_Comment_Guard g("STRUCT-FWD", name);

  if (!java_ts_only_) {
    error_ |= !gen_target_.gen_struct_fwd(node->name(), node->size_type());
  }

  return 0;
}

int
dds_visitor::visit_constant(AST_Constant* node)
{
  const char* name = node->local_name()->get_string();

  BE_Comment_Guard g("CONST", name);

  ACE_UNUSED_ARG(g);

  AST_Decl* d = ScopeAsDecl(node->defined_in());

  bool nested = d && (d->node_type() == AST_Decl::NT_interface);

  if (!java_ts_only_) {
    error_ |= !gen_target_.gen_const(node->name(), nested, node);
  }

  return 0;
}

int
dds_visitor::visit_native(AST_Native* node)
{
  const char* name = node->local_name()->get_string();

  BE_Comment_Guard g("NATIVE", name);

  ACE_UNUSED_ARG(g);

  if (!java_ts_only_) {
    error_ |= !gen_target_.gen_native(node, node->name(), node->repoID());
  }

  return 0;
}

int
dds_visitor::visit_union(AST_Union* node)
{
  const char* name = node->local_name()->get_string();

  BE_Comment_Guard g("UNION", name);

  ACE_UNUSED_ARG(g);

  vector<AST_UnionBranch*> branches;

  size_t nfields = node->nfields();

  branches.reserve(nfields);

  for (CORBA::ULong i = 0; i < nfields; ++i) {
    AST_Field** f;
    node->field(f, i);
    if (!field_check_anon(*f)) {
      error_ = true;
      return -1;
    }

    AST_UnionBranch* ub = AST_UnionBranch::narrow_from_decl(*f);

    if (!ub) {
      std::cerr << "ERROR - expected union to contain UnionBranches\n";
      error_ = true;
      return 0;
    }

    branches.push_back(ub);
  }

  if (!java_ts_only_) {
    error_ |= !gen_target_.gen_union(node, node->name(), branches, node->disc_type(),
                                     node->repoID());
  }

  return 0;
}

// *** All methods below here are unimplemented (or trivially implemented) ***

int
dds_visitor::visit_sequence(AST_Sequence*)
{
  //sequences always appear as typedefs, see visit_typedef ()
  return 0;
}

int
dds_visitor::visit_operation(AST_Operation*)
{
  // operations are taken care of by visit_interface()
  return 0;
}

int
dds_visitor::visit_field(AST_Field*)
{
  // fields are taken care of by visit_interface() for arguments and attributes
  return 0;
}

int
dds_visitor::visit_attribute(AST_Attribute*)
{
  // attributes are taken care of by visit_interface ()
  return 0;
}

int
dds_visitor::visit_array(AST_Array*)
{
  //arrays always appear as typedefs, see visit_typedef ()
  return 0;
}

//begin IDL syntactic elements that are not currently supported

int
dds_visitor::visit_valuetype(AST_ValueType*)
{
  return 0;
}

int
dds_visitor::visit_valuetype_fwd(AST_ValueTypeFwd*)
{
  return 0;
}

int
dds_visitor::visit_component(AST_Component*)
{
  return 0;
}

int
dds_visitor::visit_component_fwd(AST_ComponentFwd*)
{
  return 0;
}

int
dds_visitor::visit_eventtype(AST_EventType*)
{
  return 0;
}

int
dds_visitor::visit_eventtype_fwd(AST_EventTypeFwd*)
{
  return 0;
}

int
dds_visitor::visit_home(AST_Home*)
{
  return 0;
}

int
dds_visitor::visit_factory(AST_Factory*)
{
  return 0;
}

//no need to implement these at this level

int
dds_visitor::visit_predefined_type(AST_PredefinedType*)
{
  return 0;
}

int
dds_visitor::visit_string(AST_String*)
{
  return 0;
}

int
dds_visitor::visit_union_fwd(AST_UnionFwd* node)
{
  const char* name = node->local_name()->get_string();
  BE_Comment_Guard g("UNION-FWD", name);

  if (!java_ts_only_) {
    error_ |= !gen_target_.gen_union_fwd(node, node->name(), node->size_type());
  }

  return 0;
}

int dds_visitor::visit_union_branch(AST_UnionBranch*)
{
  return 0;
}

int dds_visitor::visit_union_label(AST_UnionLabel*)
{
  return 0;
}

int dds_visitor::visit_enum_val(AST_EnumVal*)
{
  return 0;
}

int dds_visitor::visit_expression(AST_Expression*)
{
  return 0;
}

int dds_visitor::visit_type(AST_Type*)
{
  return 0;
}

int dds_visitor::visit_argument(AST_Argument*)
{
  return 0;
}

int dds_visitor::visit_decl(AST_Decl*)
{
  return 0;
}

int dds_visitor::visit_valuebox(AST_ValueBox*)
{
  return 0;
}

int
dds_visitor::visit_template_module (AST_Template_Module*)
{
  return 0;
}

int
dds_visitor::visit_template_module_inst (AST_Template_Module_Inst*)
{
  return 0;
}

int
dds_visitor::visit_template_module_ref (AST_Template_Module_Ref*)
{
  return 0;
}

int
dds_visitor::visit_param_holder(AST_Param_Holder*)
{
  return 0;
}

int dds_visitor::visit_porttype(AST_PortType*)
{
  return 0;
}

int dds_visitor::visit_provides(AST_Provides*)
{
  return 0;
}

int dds_visitor::visit_uses(AST_Uses*)
{
  return 0;
}

int dds_visitor::visit_publishes(AST_Publishes*)
{
  return 0;
}

int dds_visitor::visit_emits(AST_Emits*)
{
  return 0;
}

int dds_visitor::visit_consumes(AST_Consumes*)
{
  return 0;
}

int dds_visitor::visit_extended_port(AST_Extended_Port*)
{
  return 0;
}

int dds_visitor::visit_mirror_port(AST_Mirror_Port*)
{
  return 0;
}

int dds_visitor::visit_connector(AST_Connector*)
{
  return 0;
}

int dds_visitor::visit_finder(AST_Finder*)
{
  return 0;
}
