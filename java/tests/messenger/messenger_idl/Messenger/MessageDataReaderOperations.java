package Messenger;
public interface MessageDataReaderOperations extends OpenDDS.DCPS.DataReaderExOperations {
  int read(Messenger.MessageSeqHolder received_data, DDS.SampleInfoSeqHolder info_seq, int max_samples, int sample_states, int view_states, int instance_states);
  int take(Messenger.MessageSeqHolder received_data, DDS.SampleInfoSeqHolder info_seq, int max_samples, int sample_states, int view_states, int instance_states);
  int read_w_condition(Messenger.MessageSeqHolder data_values, DDS.SampleInfoSeqHolder sample_infos, int max_samples, DDS.ReadCondition a_condition);
  int take_w_condition(Messenger.MessageSeqHolder data_values, DDS.SampleInfoSeqHolder sample_infos, int max_samples, DDS.ReadCondition a_condition);
  int read_next_sample(Messenger.MessageHolder received_data, DDS.SampleInfoHolder sample_info);
  int take_next_sample(Messenger.MessageHolder received_data, DDS.SampleInfoHolder sample_info);
  int read_instance(Messenger.MessageSeqHolder received_data, DDS.SampleInfoSeqHolder info_seq, int max_samples, int a_handle, int sample_states, int view_states, int instance_states);
  int take_instance(Messenger.MessageSeqHolder received_data, DDS.SampleInfoSeqHolder info_seq, int max_samples, int a_handle, int sample_states, int view_states, int instance_states);
  int read_instance_w_condition(Messenger.MessageSeqHolder received_data, DDS.SampleInfoSeqHolder sample_infos, int max_samples, int a_handle, DDS.ReadCondition a_condition);
  int take_instance_w_condition(Messenger.MessageSeqHolder received_data, DDS.SampleInfoSeqHolder sample_infos, int max_samples, int a_handle, DDS.ReadCondition a_condition);
  int read_next_instance(Messenger.MessageSeqHolder received_data, DDS.SampleInfoSeqHolder info_seq, int max_samples, int a_handle, int sample_states, int view_states, int instance_states);
  int take_next_instance(Messenger.MessageSeqHolder received_data, DDS.SampleInfoSeqHolder info_seq, int max_samples, int a_handle, int sample_states, int view_states, int instance_states);
  int read_next_instance_w_condition(Messenger.MessageSeqHolder data_values, DDS.SampleInfoSeqHolder sample_infos, int max_samples, int previous_handle, DDS.ReadCondition a_condition);
  int take_next_instance_w_condition(Messenger.MessageSeqHolder data_values, DDS.SampleInfoSeqHolder sample_infos, int max_samples, int previous_handle, DDS.ReadCondition a_condition);
  int return_loan(Messenger.MessageSeqHolder received_data, DDS.SampleInfoSeqHolder info_seq);
  int get_key_value(Messenger.MessageHolder key_holder, int handle);
  int lookup_instance(Messenger.Message instance_data);
}
