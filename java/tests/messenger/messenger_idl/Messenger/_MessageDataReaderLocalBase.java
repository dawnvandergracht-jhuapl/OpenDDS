package Messenger;
public abstract class _MessageDataReaderLocalBase extends org.omg.CORBA.LocalObject implements MessageDataReader {
  private String[] _type_ids = {"IDL:Messenger/MessageDataReader:1.0", "IDL:OpenDDS/DCPS/DataReaderEx:1.0", "IDL:DDS/DataReader:1.0", "IDL:DDS/Entity:1.0"};

  public String[] _ids() { return (String[])_type_ids.clone(); }
}
