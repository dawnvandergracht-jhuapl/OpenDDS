package Messenger;
public abstract class _MessageTypeSupportLocalBase extends org.omg.CORBA.LocalObject implements MessageTypeSupport {
  private String[] _type_ids = {"IDL:Messenger/MessageTypeSupport:1.0", "IDL:OpenDDS/DCPS/TypeSupport:1.0", "IDL:DDS/TypeSupport:1.0"};

  public String[] _ids() { return (String[])_type_ids.clone(); }
}
