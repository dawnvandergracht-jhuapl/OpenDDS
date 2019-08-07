package Messenger;
public class choice implements java.io.Serializable {
  private static choice[] __values = {
    new choice(0),
    new choice(1),
    new choice(2)
  };

  public static final int _AVALUE = 0;
  public static final choice AVALUE = __values[0];

  public static final int _BVALUE = 1;
  public static final choice BVALUE = __values[1];

  public static final int _CVALUE = 2;
  public static final choice CVALUE = __values[2];

  public int value() { return _value; }

  private int _value;

  public static choice from_int(int value) {
    if (value >= 0 && value < 3) {
      return __values[value];
    } else {
      return new choice(value);
    }
  }

  protected choice(int value) { _value = value; }

  public Object readResolve()
      throws java.io.ObjectStreamException {
    return from_int(value());
  }

}
