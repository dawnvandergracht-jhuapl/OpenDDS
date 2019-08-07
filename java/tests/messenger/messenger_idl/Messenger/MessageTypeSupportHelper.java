package Messenger;
public abstract class MessageTypeSupportHelper {
  // Any and TypeCode operations not currently implemented
  public static String id() { return "IDL:Messenger/MessageTypeSupport:1.0"; }
  public static MessageTypeSupport narrow(org.omg.CORBA.Object obj) {
    if (obj == null)
      return null;
    else if (obj instanceof MessageTypeSupport)
      return (MessageTypeSupport)obj;
    else if (!obj._is_a (id ()))
      throw new org.omg.CORBA.BAD_PARAM ();
    else
      return native_unarrow(obj);
  }

  public static MessageTypeSupport unchecked_narrow(org.omg.CORBA.Object obj) {
    if (obj == null)
      return null;
    else if (obj instanceof MessageTypeSupport)
      return (MessageTypeSupport)obj;
    else
      return native_unarrow(obj);
  }

  private native static MessageTypeSupport native_unarrow(org.omg.CORBA.Object obj);

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
