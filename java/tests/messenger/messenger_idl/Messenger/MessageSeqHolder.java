package Messenger;
public final class MessageSeqHolder {
  // TypeCode operations not currently implemented
  public Messenger.Message[] value;
  public MessageSeqHolder() {}
  public MessageSeqHolder(Messenger.Message[] initial) {
    value = initial;
  }
}
