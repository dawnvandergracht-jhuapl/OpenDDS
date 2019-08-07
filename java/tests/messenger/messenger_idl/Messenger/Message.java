package Messenger;
public final class Message implements java.io.Serializable {
  public String from;
  public String subject;
  public int subject_id;
  public String text;
  public int count;
  public String words;
  public Messenger.Choice achoice;

  public Message() {}

  public Message(String _from, String _subject, int _subject_id, String _text, int _count, String _words, Messenger.Choice _achoice) {
    from = _from;
    subject = _subject;
    subject_id = _subject_id;
    text = _text;
    count = _count;
    words = _words;
    achoice = _achoice;
  }
}
