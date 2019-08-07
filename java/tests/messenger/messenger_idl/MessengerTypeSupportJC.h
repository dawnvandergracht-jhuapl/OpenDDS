/* -*- C++ -*- */
#ifndef IDL2JNI_GENERATED_MESSENGERTYPESUPPORTJC_H
#define IDL2JNI_GENERATED_MESSENGERTYPESUPPORTJC_H
#include "MessengerTypeSupportC.h"
#include "MessengerJC.h"
#include "dds/DdsDcpsInfrastructureJC.h"
#include "dds/DdsDcpsPublicationJC.h"
#include "dds/DdsDcpsSubscriptionExtJC.h"
#include "dds/DdsDcpsTopicJC.h"
#include "dds/DdsDcpsTypeSupportExtJC.h"
#include "idl2jni_BaseJavaPeer.h"
#include "idl2jni_jni.h"
#include "idl2jni_runtime.h"
#include "messenger_idl_test_Export.h"
/* Generated by /software/OpenDDS-3.13.2/bin/idl2jni running on input file MessengerTypeSupport.idl */


/* Begin MODULE: Messenger */



/* Begin TYPEDEF: MessageSeq */

messenger_idl_test_Export
void copyToCxx (JNIEnv *jni, Messenger::MessageSeq &target, jobjectArray source);
messenger_idl_test_Export
void copyToJava (JNIEnv *jni, jobjectArray &target, const Messenger::MessageSeq &source, bool createNewObject = false);

/* End TYPEDEF: MessageSeq */


/* Begin INTERFACE: MessageTypeSupport */

messenger_idl_test_Export
void copyToCxx (JNIEnv *jni, Messenger::MessageTypeSupport_var &target, jobject source);
messenger_idl_test_Export
void copyToJava (JNIEnv *jni, jobject &target, const Messenger::MessageTypeSupport_var &source, bool createNewObject = false);

class messenger_idl_test_Export Messenger_MessageTypeSupportJavaPeer
  : public virtual OpenDDS_DCPS_TypeSupportJavaPeer
  , public virtual Messenger::MessageTypeSupport
{
public:
  Messenger_MessageTypeSupportJavaPeer (JNIEnv *jni, jobject java)
    : IDL2JNI_BaseJavaPeer (jni, java)
    , DDS_TypeSupportJavaPeer (jni, java)
    , OpenDDS_DCPS_TypeSupportJavaPeer (jni, java)
  {}

};


/* End INTERFACE: MessageTypeSupport */


/* Begin INTERFACE: MessageDataWriter */

messenger_idl_test_Export
void copyToCxx (JNIEnv *jni, Messenger::MessageDataWriter_var &target, jobject source);
messenger_idl_test_Export
void copyToJava (JNIEnv *jni, jobject &target, const Messenger::MessageDataWriter_var &source, bool createNewObject = false);

class messenger_idl_test_Export Messenger_MessageDataWriterJavaPeer
  : public virtual DDS_DataWriterJavaPeer
  , public virtual Messenger::MessageDataWriter
{
public:
  Messenger_MessageDataWriterJavaPeer (JNIEnv *jni, jobject java)
    : IDL2JNI_BaseJavaPeer (jni, java)
    , DDS_EntityJavaPeer (jni, java)
    , DDS_DataWriterJavaPeer (jni, java)
  {}

  DDS::InstanceHandle_t register_instance (const Messenger::Message& instance);

  DDS::InstanceHandle_t register_instance_w_timestamp (const Messenger::Message& instance, const DDS::Time_t& timestamp);

  DDS::ReturnCode_t unregister_instance (const Messenger::Message& instance, DDS::InstanceHandle_t handle);

  DDS::ReturnCode_t unregister_instance_w_timestamp (const Messenger::Message& instance, DDS::InstanceHandle_t handle, const DDS::Time_t& timestamp);

  DDS::ReturnCode_t write (const Messenger::Message& instance_data, DDS::InstanceHandle_t handle);

  DDS::ReturnCode_t write_w_timestamp (const Messenger::Message& instance_data, DDS::InstanceHandle_t handle, const DDS::Time_t& source_timestamp);

  DDS::ReturnCode_t dispose (const Messenger::Message& instance_data, DDS::InstanceHandle_t instance_handle);

  DDS::ReturnCode_t dispose_w_timestamp (const Messenger::Message& instance_data, DDS::InstanceHandle_t instance_handle, const DDS::Time_t& source_timestamp);

  DDS::ReturnCode_t get_key_value (Messenger::Message& key_holder, DDS::InstanceHandle_t handle);

  DDS::InstanceHandle_t lookup_instance (const Messenger::Message& instance_data);

};


/* End INTERFACE: MessageDataWriter */


/* Begin INTERFACE: MessageDataReader */

messenger_idl_test_Export
void copyToCxx (JNIEnv *jni, Messenger::MessageDataReader_var &target, jobject source);
messenger_idl_test_Export
void copyToJava (JNIEnv *jni, jobject &target, const Messenger::MessageDataReader_var &source, bool createNewObject = false);

class messenger_idl_test_Export Messenger_MessageDataReaderJavaPeer
  : public virtual OpenDDS_DCPS_DataReaderExJavaPeer
  , public virtual Messenger::MessageDataReader
{
public:
  Messenger_MessageDataReaderJavaPeer (JNIEnv *jni, jobject java)
    : IDL2JNI_BaseJavaPeer (jni, java)
    , DDS_EntityJavaPeer (jni, java)
    , DDS_DataReaderJavaPeer (jni, java)
    , OpenDDS_DCPS_DataReaderExJavaPeer (jni, java)
  {}

  DDS::ReturnCode_t read (Messenger::MessageSeq& received_data, DDS::SampleInfoSeq& info_seq, CORBA::Long max_samples, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states);

  DDS::ReturnCode_t take (Messenger::MessageSeq& received_data, DDS::SampleInfoSeq& info_seq, CORBA::Long max_samples, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states);

  DDS::ReturnCode_t read_w_condition (Messenger::MessageSeq& data_values, DDS::SampleInfoSeq& sample_infos, CORBA::Long max_samples, DDS::ReadCondition_ptr a_condition);

  DDS::ReturnCode_t take_w_condition (Messenger::MessageSeq& data_values, DDS::SampleInfoSeq& sample_infos, CORBA::Long max_samples, DDS::ReadCondition_ptr a_condition);

  DDS::ReturnCode_t read_next_sample (Messenger::Message& received_data, DDS::SampleInfo& sample_info);

  DDS::ReturnCode_t take_next_sample (Messenger::Message& received_data, DDS::SampleInfo& sample_info);

  DDS::ReturnCode_t read_instance (Messenger::MessageSeq& received_data, DDS::SampleInfoSeq& info_seq, CORBA::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states);

  DDS::ReturnCode_t take_instance (Messenger::MessageSeq& received_data, DDS::SampleInfoSeq& info_seq, CORBA::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states);

  DDS::ReturnCode_t read_instance_w_condition (Messenger::MessageSeq& received_data, DDS::SampleInfoSeq& sample_infos, CORBA::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::ReadCondition_ptr a_condition);

  DDS::ReturnCode_t take_instance_w_condition (Messenger::MessageSeq& received_data, DDS::SampleInfoSeq& sample_infos, CORBA::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::ReadCondition_ptr a_condition);

  DDS::ReturnCode_t read_next_instance (Messenger::MessageSeq& received_data, DDS::SampleInfoSeq& info_seq, CORBA::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states);

  DDS::ReturnCode_t take_next_instance (Messenger::MessageSeq& received_data, DDS::SampleInfoSeq& info_seq, CORBA::Long max_samples, DDS::InstanceHandle_t a_handle, DDS::SampleStateMask sample_states, DDS::ViewStateMask view_states, DDS::InstanceStateMask instance_states);

  DDS::ReturnCode_t read_next_instance_w_condition (Messenger::MessageSeq& data_values, DDS::SampleInfoSeq& sample_infos, CORBA::Long max_samples, DDS::InstanceHandle_t previous_handle, DDS::ReadCondition_ptr a_condition);

  DDS::ReturnCode_t take_next_instance_w_condition (Messenger::MessageSeq& data_values, DDS::SampleInfoSeq& sample_infos, CORBA::Long max_samples, DDS::InstanceHandle_t previous_handle, DDS::ReadCondition_ptr a_condition);

  DDS::ReturnCode_t return_loan (Messenger::MessageSeq& received_data, DDS::SampleInfoSeq& info_seq);

  DDS::ReturnCode_t get_key_value (Messenger::Message& key_holder, DDS::InstanceHandle_t handle);

  DDS::InstanceHandle_t lookup_instance (const Messenger::Message& instance_data);

};


/* End INTERFACE: MessageDataReader */

/* End MODULE: Messenger */
#endif /* IDL2JNI_GENERATED_MESSENGERTYPESUPPORTJC_H */
