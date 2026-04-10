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
