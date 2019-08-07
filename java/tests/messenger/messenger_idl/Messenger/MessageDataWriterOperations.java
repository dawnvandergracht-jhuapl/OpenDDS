package Messenger;
public interface MessageDataWriterOperations extends DDS.DataWriterOperations {
  int register_instance(Messenger.Message instance);
  int register_instance_w_timestamp(Messenger.Message instance, DDS.Time_t timestamp);
  int unregister_instance(Messenger.Message instance, int handle);
  int unregister_instance_w_timestamp(Messenger.Message instance, int handle, DDS.Time_t timestamp);
  int write(Messenger.Message instance_data, int handle);
  int write_w_timestamp(Messenger.Message instance_data, int handle, DDS.Time_t source_timestamp);
  int dispose(Messenger.Message instance_data, int instance_handle);
  int dispose_w_timestamp(Messenger.Message instance_data, int instance_handle, DDS.Time_t source_timestamp);
  int get_key_value(Messenger.MessageHolder key_holder, int handle);
  int lookup_instance(Messenger.Message instance_data);
}
