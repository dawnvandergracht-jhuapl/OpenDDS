package Messenger;
public abstract class MessageDataReaderHelper {
  // Any and TypeCode operations not currently implemented
  public static String id() { return "IDL:Messenger/MessageDataReader:1.0"; }
  public static MessageDataReader narrow(org.omg.CORBA.Object obj) {
    if (obj == null)
      return null;
    else if (obj instanceof MessageDataReader)
      return (MessageDataReader)obj;
    else if (!obj._is_a (id ()))
      throw new org.omg.CORBA.BAD_PARAM ();
    else
      return native_unarrow(obj);
  }

  public static MessageDataReader unchecked_narrow(org.omg.CORBA.Object obj) {
    if (obj == null)
      return null;
    else if (obj instanceof MessageDataReader)
      return (MessageDataReader)obj;
    else
      return native_unarrow(obj);
  }

  private native static MessageDataReader native_unarrow(org.omg.CORBA.Object obj);

  static {
    String propVal = System.getProperty("opendds.native.debug");
    if (propVal != null && ("1".equalsIgnoreCase(propVal) ||
        "y".equalsIgnoreCase(propVal) ||
        "yes".equalsIgnoreCase(propVal) ||
        "t".equalsIgnoreCase(propVal) ||
        "true".equalsIgnoreCase(propVal)))
      System.loadLibrary("messenger_idl_testd");
    else System.loadLibrary("messenger_idl_test");
  }

}
