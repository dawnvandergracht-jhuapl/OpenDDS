package Messenger;
public class Choice implements java.io.Serializable {
  private static Choice[] __values = {
    new Choice(0),
    new Choice(1)
  };

  public static final int _AVALUE = 0;
  public static final Choice AVALUE = __values[0];

  public static final int _BVALUE = 1;
  public static final Choice BVALUE = __values[1];

  public int value() { return _value; }

  private int _value;

  public static Choice from_int(int value) {
    if (value >= 0 && value < 2) {
      return __values[value];
    } else {
      return new Choice(value);
    }
  }

  protected Choice(int value) { _value = value; }

  public Object readResolve()
      throws java.io.ObjectStreamException {
    return from_int(value());
  }

}
