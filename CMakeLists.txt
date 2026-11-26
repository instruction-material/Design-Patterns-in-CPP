cmake_minimum_required(VERSION 3.20)
project(DesignPatternsInCpp CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(add_dpc_lab target source_file)
	add_executable(${target} ${source_file})
	target_compile_options(
		${target}
		PRIVATE
			-Wall
			-Wextra
			-Wpedantic
	)
endfunction()

add_dpc_lab(
	dpc1_factories_builders_starter
	"DPC1-Factories-and-Builders-Workshop/starter/main.cpp"
)
add_dpc_lab(
	dpc1_factories_builders_solution
	"DPC1-Factories-and-Builders-Workshop/solution/main.cpp"
)

add_dpc_lab(
	dpc2_strategy_policy_starter
	"DPC2-Strategy-and-Policy-Simulator/starter/main.cpp"
)
add_dpc_lab(
	dpc2_strategy_policy_solution
	"DPC2-Strategy-and-Policy-Simulator/solution/main.cpp"
)

add_dpc_lab(
	dpc3_observer_event_hub_starter
	"DPC3-Observer-Event-Hub/starter/main.cpp"
)
add_dpc_lab(
	dpc3_observer_event_hub_solution
	"DPC3-Observer-Event-Hub/solution/main.cpp"
)

add_dpc_lab(
	dpc4_facade_adapter_starter
	"DPC4-Facade-Adapter-Import-Tool/starter/main.cpp"
)
add_dpc_lab(
	dpc4_facade_adapter_solution
	"DPC4-Facade-Adapter-Import-Tool/solution/main.cpp"
)

add_dpc_lab(
	dpc5_command_state_starter
	"DPC5-Command-and-State-Editor/starter/main.cpp"
)
add_dpc_lab(
	dpc5_command_state_solution
	"DPC5-Command-and-State-Editor/solution/main.cpp"
)

add_dpc_lab(
	dpc6_composite_scene_tree_starter
	"DPC6-Composite-Scene-Tree/starter/main.cpp"
)
add_dpc_lab(
	dpc6_composite_scene_tree_solution
	"DPC6-Composite-Scene-Tree/solution/main.cpp"
)

add_dpc_lab(
	dpc7_raii_resource_manager_starter
	"DPC7-RAII-Resource-Manager/starter/main.cpp"
)
add_dpc_lab(
	dpc7_raii_resource_manager_solution
	"DPC7-RAII-Resource-Manager/solution/main.cpp"
)

add_dpc_lab(
	dpc8_legacy_refactor_capstone_starter
	"DPC8-Legacy-Refactor-Capstone/starter/main.cpp"
)
add_dpc_lab(
	dpc8_legacy_refactor_capstone_solution
	"DPC8-Legacy-Refactor-Capstone/solution/main.cpp"
)

add_dpc_lab(dpc_command_scanner_starter "DPC-15-dpc7-command-and-state-supplemental-2/starter/main.cpp")
add_dpc_lab(dpc_command_scanner_solution "DPC-15-dpc7-command-and-state-supplemental-2/solution/main.cpp")
add_dpc_lab(dpc_command_redo_starter "DPC-16-dpc7-command-and-state-supplemental-3/starter/main.cpp")
add_dpc_lab(dpc_command_redo_solution "DPC-16-dpc7-command-and-state-supplemental-3/solution/main.cpp")

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSON_C REQUIRED IMPORTED_TARGET json-c>=0.15)
target_link_libraries(dpc4_facade_adapter_solution PRIVATE PkgConfig::JSON_C)

add_dpc_lab(dpc_schedule_starter "DPC-09-dpc4-strategy-and-policy-based-design-supplemental-2/starter/main.cpp")
add_dpc_lab(dpc_schedule_solution "DPC-09-dpc4-strategy-and-policy-based-design-supplemental-2/solution/main.cpp")
add_dpc_lab(dpc_alarm_starter "DPC-10-dpc4-strategy-and-policy-based-design-supplemental-3/starter/main.cpp")
add_dpc_lab(dpc_alarm_solution "DPC-10-dpc4-strategy-and-policy-based-design-supplemental-3/solution/main.cpp")
add_dpc_lab(dpc_match_feed_starter "DPC-11-dpc5-observer-and-event-flow-supplemental-2/starter/main.cpp")
add_dpc_lab(dpc_match_feed_solution "DPC-11-dpc5-observer-and-event-flow-supplemental-2/solution/main.cpp")
add_dpc_lab(dpc_connection_starter "DPC-12-dpc5-observer-and-event-flow-supplemental-3/starter/main.cpp")
add_dpc_lab(dpc_connection_solution "DPC-12-dpc5-observer-and-event-flow-supplemental-3/solution/main.cpp")

add_dpc_lab(dpc_playlist_starter "DPC-17-dpc8-composite-and-iterator-supplemental-2/starter/main.cpp")
add_dpc_lab(dpc_playlist_solution "DPC-17-dpc8-composite-and-iterator-supplemental-2/solution/main.cpp")
add_dpc_lab(dpc_outline_starter "DPC-18-dpc8-composite-and-iterator-supplemental-3/starter/main.cpp")
add_dpc_lab(dpc_outline_solution "DPC-18-dpc8-composite-and-iterator-supplemental-3/solution/main.cpp")

add_dpc_lab(dpc_draft_inbox_starter "DPC-03-dpc1-why-patterns-look-different-in-modern-cpp-supplemental-2/starter/main.cpp")
add_dpc_lab(dpc_draft_inbox_solution "DPC-03-dpc1-why-patterns-look-different-in-modern-cpp-supplemental-2/solution/main.cpp")
add_dpc_lab(dpc_tour_starter "DPC-04-dpc1-why-patterns-look-different-in-modern-cpp-supplemental-3/starter/main.cpp")
add_dpc_lab(dpc_tour_solution "DPC-04-dpc1-why-patterns-look-different-in-modern-cpp-supplemental-3/solution/main.cpp")
add_dpc_lab(dpc_probe_starter "DPC-05-dpc2-design-foundations-supplemental-2/starter/main.cpp")
add_dpc_lab(dpc_probe_solution "DPC-05-dpc2-design-foundations-supplemental-2/solution/main.cpp")
add_dpc_lab(dpc_slot_starter "DPC-06-dpc2-design-foundations-supplemental-3/starter/main.cpp")
add_dpc_lab(dpc_slot_solution "DPC-06-dpc2-design-foundations-supplemental-3/solution/main.cpp")

add_dpc_lab(dpc_notice_trace_starter "DPC-13-dpc6-decorator-adapter-and-facade-supplemental-2/starter/main.cpp")
add_dpc_lab(dpc_notice_trace_solution "DPC-13-dpc6-decorator-adapter-and-facade-supplemental-2/solution/main.cpp")
add_dpc_lab(dpc_audio_guide_starter "DPC-14-dpc6-decorator-adapter-and-facade-supplemental-3/starter/main.cpp")
add_dpc_lab(dpc_audio_guide_solution "DPC-14-dpc6-decorator-adapter-and-facade-supplemental-3/solution/main.cpp")
add_dpc_lab(dpc_channel_lease_starter "DPC-21-dpc10-patterns-for-resource-management-supplemental-2/starter/main.cpp")
add_dpc_lab(dpc_channel_lease_solution "DPC-21-dpc10-patterns-for-resource-management-supplemental-2/solution/main.cpp")
add_dpc_lab(dpc_frame_batch_starter "DPC-22-dpc10-patterns-for-resource-management-supplemental-3/starter/main.cpp")
add_dpc_lab(dpc_frame_batch_solution "DPC-22-dpc10-patterns-for-resource-management-supplemental-3/solution/main.cpp")

add_dpc_lab(dpc_loan_fee_starter "DPC-23-dpc11-legacy-refactoring-lab-supplemental-2/starter/main.cpp")
add_dpc_lab(dpc_loan_fee_solution "DPC-23-dpc11-legacy-refactoring-lab-supplemental-2/solution/main.cpp")
add_dpc_lab(dpc_booking_snapshot_starter "DPC-24-dpc11-legacy-refactoring-lab-supplemental-3/starter/main.cpp")
add_dpc_lab(dpc_booking_snapshot_solution "DPC-24-dpc11-legacy-refactoring-lab-supplemental-3/solution/main.cpp")
add_dpc_lab(dpc_studio_plan_starter "DPC-25-dpc12-capstone-studio-supplemental-2/starter/main.cpp")
add_dpc_lab(dpc_studio_plan_solution "DPC-25-dpc12-capstone-studio-supplemental-2/solution/main.cpp")
add_dpc_lab(dpc_service_queue_starter "DPC-26-dpc12-capstone-studio-supplemental-3/starter/main.cpp")
add_dpc_lab(dpc_service_queue_solution "DPC-26-dpc12-capstone-studio-supplemental-3/solution/main.cpp")

add_dpc_lab(dpc_instrument_bench_starter "DPC-01-pattern-implementation-lab-14/starter/main.cpp")
add_dpc_lab(dpc_instrument_bench_solution "DPC-01-pattern-implementation-lab-14/solution/main.cpp")
add_dpc_lab(dpc_sign_strategy_starter "DPC-02-pattern-implementation-lab-15/starter/main.cpp")
add_dpc_lab(dpc_sign_strategy_solution "DPC-02-pattern-implementation-lab-15/solution/main.cpp")
add_dpc_lab(dpc_seat_intake_starter "DPC-03-pattern-implementation-lab-16/starter/main.cpp")
add_dpc_lab(dpc_seat_intake_solution "DPC-03-pattern-implementation-lab-16/solution/main.cpp")
add_dpc_lab(dpc_kit_report_starter "DPC-04-pattern-implementation-lab-17/starter/main.cpp")
add_dpc_lab(dpc_kit_report_solution "DPC-04-pattern-implementation-lab-17/solution/main.cpp")

include(CTest)
if(BUILD_TESTING)
    add_dpc_lab(dpc_dashboard_family_check "tests/dashboard_family.cpp")
    add_test(NAME dashboard_uses_selected_product_family COMMAND dpc_dashboard_family_check)
    add_dpc_lab(dpc_scope_exit_check "tests/scope_exit.cpp")
    add_test(NAME scope_exit_runs_once COMMAND dpc_scope_exit_check)
endif()
