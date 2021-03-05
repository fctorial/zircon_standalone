






extern zx_status_t __zx_bti_create ( zx_handle_t iommu, uint32_t options, uint64_t bti_id, zx_handle_t* out);






extern zx_status_t __zx_bti_pin ( zx_handle_t handle, uint32_t options, zx_handle_t vmo, uint64_t offset, uint64_t size, zx_paddr_t* addrs, size_t num_addrs, zx_handle_t* pmt);
extern zx_status_t __zx_bti_release_quarantine ( zx_handle_t handle);



extern zx_status_t __zx_cache_flush ( const void* addr, size_t size, uint32_t options);





extern zx_status_t __zx_channel_create ( uint32_t options, zx_handle_t* out0, zx_handle_t* out1);





extern zx_status_t __zx_channel_read ( zx_handle_t handle, uint32_t options, void* bytes, zx_handle_t* handles, uint32_t num_bytes, uint32_t num_handles, uint32_t* actual_bytes, uint32_t* actual_handles);
extern zx_status_t __zx_channel_read_etc ( zx_handle_t handle, uint32_t options, void* bytes, zx_handle_info_t* handles, uint32_t num_bytes, uint32_t num_handles, uint32_t* actual_bytes, uint32_t* actual_handles);
extern zx_status_t __zx_channel_write ( zx_handle_t handle, uint32_t options, const void* bytes, uint32_t num_bytes, const zx_handle_t* handles, uint32_t num_handles);
extern zx_status_t __zx_channel_write_etc ( zx_handle_t handle, uint32_t options, const void* bytes, uint32_t num_bytes, zx_handle_disposition_t* handles, uint32_t num_handles);
extern zx_status_t __zx_channel_call ( zx_handle_t handle, uint32_t options, zx_time_t deadline, const zx_channel_call_args_t* args, uint32_t* actual_bytes, uint32_t* actual_handles);
extern zx_status_t __zx_channel_call_etc ( zx_handle_t handle, uint32_t options, zx_time_t deadline, zx_channel_call_etc_args_t* args, uint32_t* actual_bytes, uint32_t* actual_handles);
extern zx_status_t __zx_clock_get ( zx_clock_t clock_id, zx_time_t* out);




extern zx_time_t __zx_clock_get_monotonic (void);


extern zx_status_t __zx_clock_adjust ( zx_handle_t handle, zx_clock_t clock_id, int64_t offset);





extern zx_status_t __zx_clock_create ( uint64_t options, const void* args, zx_handle_t* out);





extern zx_status_t __zx_clock_read ( zx_handle_t handle, zx_time_t* now);




extern zx_status_t __zx_clock_get_details ( zx_handle_t handle, uint64_t options, void* details);





extern zx_status_t __zx_clock_update ( zx_handle_t handle, uint64_t options, const void* args);





extern void __zx_cprng_draw ( void* buffer, size_t buffer_size);




extern zx_status_t __zx_cprng_add_entropy ( const void* buffer, size_t buffer_size);




extern zx_status_t __zx_debug_read ( zx_handle_t handle, char* buffer, size_t buffer_size, size_t* actual);






extern zx_status_t __zx_debug_write ( const char* buffer, size_t buffer_size);




extern zx_status_t __zx_debug_send_command ( zx_handle_t resource, const char* buffer, size_t buffer_size);





extern zx_status_t __zx_debuglog_create ( zx_handle_t resource, uint32_t options, zx_handle_t* out);





extern zx_status_t __zx_debuglog_write ( zx_handle_t handle, uint32_t options, const void* buffer, size_t buffer_size);






extern zx_status_t __zx_debuglog_read ( zx_handle_t handle, uint32_t options, void* buffer, size_t buffer_size);






extern zx_status_t __zx_event_create ( uint32_t options, zx_handle_t* out);




extern zx_status_t __zx_eventpair_create ( uint32_t options, zx_handle_t* out0, zx_handle_t* out1);





extern zx_status_t __zx_exception_get_thread ( zx_handle_t handle, zx_handle_t* out);




extern zx_status_t __zx_exception_get_process ( zx_handle_t handle, zx_handle_t* out);




extern zx_status_t __zx_fifo_create ( size_t elem_count, size_t elem_size, uint32_t options, zx_handle_t* out0, zx_handle_t* out1);







extern zx_status_t __zx_fifo_read ( zx_handle_t handle, size_t elem_size, void* data, size_t data_size, size_t* actual_count);







extern zx_status_t __zx_fifo_write ( zx_handle_t handle, size_t elem_size, const void* data, size_t count, size_t* actual_count);







extern zx_status_t __zx_framebuffer_get_info ( zx_handle_t resource, uint32_t* format, uint32_t* width, uint32_t* height, uint32_t* stride);







extern zx_status_t __zx_framebuffer_set_range ( zx_handle_t resource, zx_handle_t vmo, uint32_t len, uint32_t format, uint32_t width, uint32_t height, uint32_t stride);
extern zx_status_t __zx_futex_wait ( const zx_futex_t* value_ptr, zx_futex_t current_value, zx_handle_t new_futex_owner, zx_time_t deadline);






extern zx_status_t __zx_futex_wake ( const zx_futex_t* value_ptr, uint32_t wake_count);




extern zx_status_t __zx_futex_requeue ( const zx_futex_t* value_ptr, uint32_t wake_count, zx_futex_t current_value, const zx_futex_t* requeue_ptr, uint32_t requeue_count, zx_handle_t new_requeue_owner);
extern zx_status_t __zx_futex_wake_single_owner ( const zx_futex_t* value_ptr);



extern zx_status_t __zx_futex_requeue_single_owner ( const zx_futex_t* value_ptr, zx_futex_t current_value, const zx_futex_t* requeue_ptr, uint32_t requeue_count, zx_handle_t new_requeue_owner);







extern zx_status_t __zx_futex_get_owner ( const zx_futex_t* value_ptr, zx_koid_t* koid);




extern zx_status_t __zx_guest_create ( zx_handle_t resource, uint32_t options, zx_handle_t* guest_handle, zx_handle_t* vmar_handle);






extern zx_status_t __zx_guest_set_trap ( zx_handle_t handle, uint32_t kind, zx_vaddr_t addr, size_t size, zx_handle_t port_handle, uint64_t key);
extern zx_status_t __zx_handle_close ( zx_handle_t handle);



extern zx_status_t __zx_handle_close_many ( const zx_handle_t* handles, size_t num_handles);




extern zx_status_t __zx_handle_duplicate ( zx_handle_t handle, zx_rights_t rights, zx_handle_t* out);





extern zx_status_t __zx_handle_replace ( zx_handle_t handle, zx_rights_t rights, zx_handle_t* out);





extern zx_status_t __zx_interrupt_create ( zx_handle_t src_obj, uint32_t src_num, uint32_t options, zx_handle_t* out_handle);






extern zx_status_t __zx_interrupt_bind ( zx_handle_t handle, zx_handle_t port_handle, uint64_t key, uint32_t options);






extern zx_status_t __zx_interrupt_wait ( zx_handle_t handle, zx_time_t* out_timestamp);




extern zx_status_t __zx_interrupt_destroy ( zx_handle_t handle);



extern zx_status_t __zx_interrupt_ack ( zx_handle_t handle);



extern zx_status_t __zx_interrupt_trigger ( zx_handle_t handle, uint32_t options, zx_time_t timestamp);





extern zx_status_t __zx_interrupt_bind_vcpu ( zx_handle_t handle, zx_handle_t vcpu, uint32_t options);





extern zx_status_t __zx_iommu_create ( zx_handle_t resource, uint32_t type, const void* desc, size_t desc_size, zx_handle_t* out);







extern zx_status_t __zx_ioports_request ( zx_handle_t resource, uint16_t io_addr, uint32_t len);





extern zx_status_t __zx_ioports_release ( zx_handle_t resource, uint16_t io_addr, uint32_t len);





extern zx_status_t __zx_job_create ( zx_handle_t parent_job, uint32_t options, zx_handle_t* out);





extern zx_status_t __zx_job_set_policy ( zx_handle_t handle, uint32_t options, uint32_t topic, const void* policy, uint32_t policy_size);







extern zx_status_t __zx_job_set_critical ( zx_handle_t job, uint32_t options, zx_handle_t process);





extern zx_status_t __zx_ktrace_read ( zx_handle_t handle, void* data, uint32_t offset, size_t data_size, size_t* actual);







extern zx_status_t __zx_ktrace_control ( zx_handle_t handle, uint32_t action, uint32_t options, void* ptr);






extern zx_status_t __zx_ktrace_write ( zx_handle_t handle, uint32_t id, uint32_t arg0, uint32_t arg1);






extern zx_status_t __zx_nanosleep ( zx_time_t deadline);



extern zx_ticks_t __zx_ticks_get (void);


extern __CONST zx_ticks_t __zx_ticks_per_second (void);


extern zx_time_t __zx_deadline_after ( zx_duration_t nanoseconds);



extern zx_status_t __zx_vmar_unmap_handle_close_thread_exit ( zx_handle_t vmar_handle, zx_vaddr_t addr, size_t size, zx_handle_t close_handle);






extern __NO_RETURN void __zx_futex_wake_handle_close_thread_exit ( const zx_futex_t* value_ptr, uint32_t wake_count, int32_t new_value, zx_handle_t close_handle);






extern zx_status_t __zx_msi_allocate ( zx_handle_t handle, uint32_t count, zx_handle_t* out_allocation);





extern zx_status_t __zx_msi_create ( zx_handle_t handle, uint32_t options, uint32_t msi_id, zx_handle_t vmo, size_t vmo_offset, zx_handle_t* out_interrupt);
extern zx_status_t __zx_mtrace_control ( zx_handle_t handle, uint32_t kind, uint32_t action, uint32_t options, void* ptr, size_t ptr_size);
extern zx_status_t __zx_object_wait_one ( zx_handle_t handle, zx_signals_t signals, zx_time_t deadline, zx_signals_t* observed);






extern zx_status_t __zx_object_wait_many ( zx_wait_item_t* items, size_t num_items, zx_time_t deadline);





extern zx_status_t __zx_object_wait_async ( zx_handle_t handle, zx_handle_t port, uint64_t key, zx_signals_t signals, uint32_t options);







extern zx_status_t __zx_object_signal ( zx_handle_t handle, uint32_t clear_mask, uint32_t set_mask);





extern zx_status_t __zx_object_signal_peer ( zx_handle_t handle, uint32_t clear_mask, uint32_t set_mask);





extern zx_status_t __zx_object_get_property ( zx_handle_t handle, uint32_t property, void* value, size_t value_size);






extern zx_status_t __zx_object_set_property ( zx_handle_t handle, uint32_t property, const void* value, size_t value_size);






extern zx_status_t __zx_object_get_info ( zx_handle_t handle, uint32_t topic, void* buffer, size_t buffer_size, size_t* actual, size_t* avail);
extern zx_status_t __zx_object_get_child ( zx_handle_t handle, uint64_t koid, zx_rights_t rights, zx_handle_t* out);






extern zx_status_t __zx_object_set_profile ( zx_handle_t handle, zx_handle_t profile, uint32_t options);





extern zx_status_t __zx_pager_create ( uint32_t options, zx_handle_t* out);




extern zx_status_t __zx_pager_create_vmo ( zx_handle_t pager, uint32_t options, zx_handle_t port, uint64_t key, uint64_t size, zx_handle_t* out);
extern zx_status_t __zx_pager_detach_vmo ( zx_handle_t pager, zx_handle_t vmo);




extern zx_status_t __zx_pager_supply_pages ( zx_handle_t pager, zx_handle_t pager_vmo, uint64_t offset, uint64_t length, zx_handle_t aux_vmo, uint64_t aux_offset);
extern zx_status_t __zx_pager_op_range ( zx_handle_t pager, uint32_t op, zx_handle_t pager_vmo, uint64_t offset, uint64_t length, uint64_t data);
extern zx_status_t __zx_pc_firmware_tables ( zx_handle_t handle, zx_paddr_t* acpi_rsdp, zx_paddr_t* smbios);





extern zx_status_t __zx_pci_get_nth_device ( zx_handle_t handle, uint32_t index, zx_pcie_device_info_t* out_info, zx_handle_t* out_handle);






extern zx_status_t __zx_pci_enable_bus_master ( zx_handle_t handle, uint32_t enable);




extern zx_status_t __zx_pci_reset_device ( zx_handle_t handle);



extern zx_status_t __zx_pci_config_read ( zx_handle_t handle, uint16_t offset, size_t width, uint32_t* out_val);






extern zx_status_t __zx_pci_config_write ( zx_handle_t handle, uint16_t offset, size_t width, uint32_t val);






extern zx_status_t __zx_pci_cfg_pio_rw ( zx_handle_t handle, uint8_t bus, uint8_t dev, uint8_t func, uint8_t offset, uint32_t* val, size_t width, uint32_t write);
extern zx_status_t __zx_pci_get_bar ( zx_handle_t handle, uint32_t bar_num, zx_pci_bar_t* out_bar, zx_handle_t* out_handle);






extern zx_status_t __zx_pci_map_interrupt ( zx_handle_t handle, int32_t which_irq, zx_handle_t* out_handle);





extern zx_status_t __zx_pci_query_irq_mode ( zx_handle_t handle, uint32_t mode, uint32_t* out_max_irqs);





extern zx_status_t __zx_pci_set_irq_mode ( zx_handle_t handle, uint32_t mode, uint32_t requested_irq_count);





extern zx_status_t __zx_pci_init ( zx_handle_t handle, const zx_pci_init_arg_t* init_buf, uint32_t len);





extern zx_status_t __zx_pci_add_subtract_io_range ( zx_handle_t handle, uint32_t mmio, uint64_t base, uint64_t len, uint32_t add);







extern zx_status_t __zx_pmt_unpin ( zx_handle_t handle);



extern zx_status_t __zx_port_create ( uint32_t options, zx_handle_t* out);




extern zx_status_t __zx_port_queue ( zx_handle_t handle, const zx_port_packet_t* packet);




extern zx_status_t __zx_port_wait ( zx_handle_t handle, zx_time_t deadline, zx_port_packet_t* packet);





extern zx_status_t __zx_port_cancel ( zx_handle_t handle, zx_handle_t source, uint64_t key);





extern __NO_RETURN void __zx_process_exit ( int64_t retcode);



extern zx_status_t __zx_process_create ( zx_handle_t job, const char* name, size_t name_size, uint32_t options, zx_handle_t* proc_handle, zx_handle_t* vmar_handle);
extern zx_status_t __zx_process_start ( zx_handle_t handle, zx_handle_t thread, zx_vaddr_t entry, zx_vaddr_t stack, zx_handle_t arg1, uintptr_t arg2);
extern zx_status_t __zx_process_read_memory ( zx_handle_t handle, zx_vaddr_t vaddr, void* buffer, size_t buffer_size, size_t* actual);







extern zx_status_t __zx_process_write_memory ( zx_handle_t handle, zx_vaddr_t vaddr, const void* buffer, size_t buffer_size, size_t* actual);







extern zx_status_t __zx_profile_create ( zx_handle_t root_job, uint32_t options, const zx_profile_info_t* profile, zx_handle_t* out);






extern zx_status_t __zx_resource_create ( zx_handle_t parent_rsrc, uint32_t options, uint64_t base, size_t size, const char* name, size_t name_size, zx_handle_t* resource_out);
extern zx_status_t __zx_smc_call ( zx_handle_t handle, const zx_smc_parameters_t* parameters, zx_smc_result_t* out_smc_result);





extern zx_status_t __zx_socket_create ( uint32_t options, zx_handle_t* out0, zx_handle_t* out1);





extern zx_status_t __zx_socket_write ( zx_handle_t handle, uint32_t options, const void* buffer, size_t buffer_size, size_t* actual);







extern zx_status_t __zx_socket_read ( zx_handle_t handle, uint32_t options, void* buffer, size_t buffer_size, size_t* actual);







extern zx_status_t __zx_socket_shutdown ( zx_handle_t handle, uint32_t options);




extern zx_status_t __zx_stream_create ( uint32_t options, zx_handle_t vmo, zx_off_t seek, zx_handle_t* out_stream);






extern zx_status_t __zx_stream_writev ( zx_handle_t handle, uint32_t options, const zx_iovec_t* vector, size_t num_vector, size_t* actual);







extern zx_status_t __zx_stream_writev_at ( zx_handle_t handle, uint32_t options, zx_off_t offset, const zx_iovec_t* vector, size_t num_vector, size_t* actual);
extern zx_status_t __zx_stream_readv ( zx_handle_t handle, uint32_t options, zx_iovec_t* vector, size_t num_vector, size_t* actual);







extern zx_status_t __zx_stream_readv_at ( zx_handle_t handle, uint32_t options, zx_off_t offset, zx_iovec_t* vector, size_t num_vector, size_t* actual);
extern zx_status_t __zx_stream_seek ( zx_handle_t handle, zx_stream_seek_origin_t whence, int64_t offset, zx_off_t* out_seek);






extern __CONST uint32_t __zx_system_get_dcache_line_size (void);


extern __CONST uint32_t __zx_system_get_num_cpus (void);


extern __CONST zx_string_view_t __zx_system_get_version_string (void);


extern __CONST uint32_t __zx_system_get_page_size (void);


extern uint64_t __zx_system_get_physmem (void);


extern zx_status_t __zx_system_get_features ( uint32_t kind, uint32_t* features);




extern zx_status_t __zx_system_get_event ( zx_handle_t root_job, uint32_t kind, zx_handle_t* event);





extern zx_status_t __zx_system_mexec ( zx_handle_t resource, zx_handle_t kernel_vmo, zx_handle_t bootimage_vmo);





extern zx_status_t __zx_system_mexec_payload_get ( zx_handle_t resource, void* buffer, size_t buffer_size);





extern zx_status_t __zx_system_powerctl ( zx_handle_t resource, uint32_t cmd, const zx_system_powerctl_arg_t* arg);





extern zx_status_t __zx_task_suspend ( zx_handle_t handle, zx_handle_t* token);




extern zx_status_t __zx_task_suspend_token ( zx_handle_t handle, zx_handle_t* token);




extern zx_status_t __zx_task_create_exception_channel ( zx_handle_t handle, uint32_t options, zx_handle_t* out);





extern zx_status_t __zx_task_kill ( zx_handle_t handle);



extern __NO_RETURN void __zx_thread_exit (void);


extern zx_status_t __zx_thread_create ( zx_handle_t process, const char* name, size_t name_size, uint32_t options, zx_handle_t* out);







extern zx_status_t __zx_thread_start ( zx_handle_t handle, zx_vaddr_t thread_entry, zx_vaddr_t stack, uintptr_t arg1, uintptr_t arg2);







extern zx_status_t __zx_thread_read_state ( zx_handle_t handle, uint32_t kind, void* buffer, size_t buffer_size);






extern zx_status_t __zx_thread_write_state ( zx_handle_t handle, uint32_t kind, const void* buffer, size_t buffer_size);






extern zx_status_t __zx_timer_create ( uint32_t options, zx_clock_t clock_id, zx_handle_t* out);





extern zx_status_t __zx_timer_set ( zx_handle_t handle, zx_time_t deadline, zx_duration_t slack);





extern zx_status_t __zx_timer_cancel ( zx_handle_t handle);



extern zx_status_t __zx_vcpu_create ( zx_handle_t guest, uint32_t options, zx_vaddr_t entry, zx_handle_t* out);






extern zx_status_t __zx_vcpu_resume ( zx_handle_t handle, zx_port_packet_t* packet);




extern zx_status_t __zx_vcpu_interrupt ( zx_handle_t handle, uint32_t vector);




extern zx_status_t __zx_vcpu_read_state ( zx_handle_t handle, uint32_t kind, void* buffer, size_t buffer_size);






extern zx_status_t __zx_vcpu_write_state ( zx_handle_t handle, uint32_t kind, const void* buffer, size_t buffer_size);






extern zx_status_t __zx_vmar_allocate ( zx_handle_t parent_vmar, zx_vm_option_t options, size_t offset, size_t size, zx_handle_t* child_vmar, zx_vaddr_t* child_addr);
extern zx_status_t __zx_vmar_destroy ( zx_handle_t handle);



extern zx_status_t __zx_vmar_map ( zx_handle_t handle, zx_vm_option_t options, size_t vmar_offset, zx_handle_t vmo, uint64_t vmo_offset, size_t len, zx_vaddr_t* mapped_addr);
extern zx_status_t __zx_vmar_unmap ( zx_handle_t handle, zx_vaddr_t addr, size_t len);





extern zx_status_t __zx_vmar_protect ( zx_handle_t handle, zx_vm_option_t options, zx_vaddr_t addr, size_t len);






extern zx_status_t __zx_vmar_op_range ( zx_handle_t handle, uint32_t op, zx_vaddr_t address, size_t size, void* buffer, size_t buffer_size);
extern zx_status_t __zx_vmo_create ( uint64_t size, uint32_t options, zx_handle_t* out);





extern zx_status_t __zx_vmo_read ( zx_handle_t handle, void* buffer, uint64_t offset, size_t buffer_size);






extern zx_status_t __zx_vmo_write ( zx_handle_t handle, const void* buffer, uint64_t offset, size_t buffer_size);






extern zx_status_t __zx_vmo_get_size ( zx_handle_t handle, uint64_t* size);




extern zx_status_t __zx_vmo_set_size ( zx_handle_t handle, uint64_t size);




extern zx_status_t __zx_vmo_op_range ( zx_handle_t handle, uint32_t op, uint64_t offset, uint64_t size, void* buffer, size_t buffer_size);
extern zx_status_t __zx_vmo_create_child ( zx_handle_t handle, uint32_t options, uint64_t offset, uint64_t size, zx_handle_t* out);







extern zx_status_t __zx_vmo_set_cache_policy ( zx_handle_t handle, uint32_t cache_policy);




extern zx_status_t __zx_vmo_replace_as_executable ( zx_handle_t handle, zx_handle_t vmex, zx_handle_t* out);





extern zx_status_t __zx_vmo_create_contiguous ( zx_handle_t bti, size_t size, uint32_t alignment_log2, zx_handle_t* out);






extern zx_status_t __zx_vmo_create_physical ( zx_handle_t resource, zx_paddr_t paddr, size_t size, zx_handle_t* out);
