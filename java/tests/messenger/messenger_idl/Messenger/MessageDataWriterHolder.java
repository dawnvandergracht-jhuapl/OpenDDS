package Messenger;
public final class MessageDataWriterHolder {
  // TypeCode operations not currently implemented
  public MessageDataWriter value;
  public MessageDataWriterHolder() {}
  public MessageDataWriterHolder(MessageDataWriter initial) {
    value = initial;
  }
}
