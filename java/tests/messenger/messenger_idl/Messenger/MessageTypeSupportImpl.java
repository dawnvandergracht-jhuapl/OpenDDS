package Messenger;
public class MessageTypeSupportImpl extends _MessageTypeSupportTAOPeer {
    public MessageTypeSupportImpl() {
        super(_jni_init());
    }
    private static native long _jni_init();
}
