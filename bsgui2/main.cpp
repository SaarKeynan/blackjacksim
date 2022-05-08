// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <iostream>
#include <string>
#include <imgui_internal.h>
#include "ConditionObjType.h"
#include "Rules.h"
#include "ConditionObject.h"
#include "Condition.h"
#include "BSTable.h"

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void makeTable(int rowStart, int rowEnd, std::string idStart, char* table);
char* printTable(char* table, int lastIndex);
void setTable(char* table, char* values, int size);

int main(int, char**)
{
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;
	const char* glsl_version = "#version 330";

	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Our state
	bool show_demo_window = true;
	bool show_another_window = true;
	bool basic_strategy_window = true;
	bool run_sim_window = true;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	char* hardValueTable = (char*)calloc(17 * 10 * 2, 1);
	char* softValueTable = (char*)calloc(10 * 8 * 2, 1);
	char* splitTable = (char*)calloc(10 * 10 * 2, 1);
	char* surrenderTable = (char*)calloc(17 * 10 * 2, 1);
	char defHvt[171] = "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHDDDDHHHHHDDDDDDDDHHDDDDDDDDDDHHSSSHHHHHSSSSSHHHHHSSSSSHHHHHSSSSSHHHHHSSSSSHHHHHSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS";
	char defSvt[81] = "DDDDDDDHHHHHHHHDDHHHHHHHHDDDHHHHHHHDDDHHHHHHHDDDDHHHHSSDDDDDSSSSSDSSSSSSSSSSSSSS";
	char defSplit[101] = "NNNNYYYYYYNNNNYYYYYYNNNNNYYNNNNNNNNNNNNNNNNNNYYYYYNNNNYYYYYYYYYYYYYYYYNNYYNYYYYYNNNNNNNNNNYYYYYYYYYY";
	char defSurr[171] = "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNYYYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN";
	bool FALSE = false, TRUE = true;
	Rules gameRules = Rules();
	ConditionObject objects[] = {
		{"False", &FALSE, BOOLEAN},
		{"True", &TRUE, BOOLEAN},
		{"Split Aces", &gameRules.SPLIT_ACES, BOOLEAN},
		{"Play after split aces", &gameRules.PLAY_AFTER_SPLIT_ACES, BOOLEAN},
		{"Resplit aces", &gameRules.RESPLIT_ACES, BOOLEAN},
		{"Surrender", &gameRules.SURRENDER, BOOLEAN},
		{"DAS", &gameRules.DOUBLE_AFTER_SPLIT, BOOLEAN},
		{"Double amount", &gameRules.DOUBLE_AMOUNT, NUMBER},
		{"Resplit amount", &gameRules.RESPLIT_AMOUNT, NUMBER},
		{"Blackjack ratio", &gameRules.BLACKJACK_RATIO, NUMBER},
		{"Deck penetration", &gameRules.DECK_PENETRATION, NUMBER}
	};
	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::ShowDemoWindow(&show_demo_window);
		static ImVec2 cell_padding(0.0f, 0.0f);
		{
			ImGui::Begin("Simulation Window", &run_sim_window);
			ImGui::Checkbox("Split aces", &gameRules.SPLIT_ACES);
			if (gameRules.SPLIT_ACES) {
				ImGui::Checkbox("Play after split aces", &gameRules.PLAY_AFTER_SPLIT_ACES);
				if (gameRules.PLAY_AFTER_SPLIT_ACES) {
					ImGui::Checkbox("Resplit aces", &gameRules.RESPLIT_ACES);
				}
			}
			ImGui::Checkbox("DAS", &gameRules.DOUBLE_AFTER_SPLIT);
			ImGui::Checkbox("Surrender", &gameRules.SURRENDER);
			if (ImGui::Button("Run Simulation")) {

			}
			ImGui::End();
		}
		{
			ImGui::Begin("Basic Strategy Table", &basic_strategy_window);
			ImGui::Text("Hard totals:");

			ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, cell_padding);
			if (ImGui::BeginTable("Hard Totals", 11, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner | ImGuiTableFlags_NoHostExtendX | ImGuiTableFlags_NoPadInnerX)) {
				makeTable(3, 20, "##hard", hardValueTable);
			}
			ImGui::SameLine();
			if (ImGui::BeginTable("Soft Totals", 11, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner | ImGuiTableFlags_NoHostExtendX | ImGuiTableFlags_NoPadInnerX)) {
				makeTable(12, 20, "##soft", softValueTable);
			}
			ImGui::SameLine();
			if (ImGui::BeginTable("Split", 11, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner | ImGuiTableFlags_NoHostExtendX | ImGuiTableFlags_NoPadInnerX)) {
				makeTable(2, 11, "##split", splitTable);
			}
			ImGui::PopStyleVar();
			if (ImGui::Button("Print")) {
				char* hvt = printTable(hardValueTable, 17 * 10);
				char* svt = printTable(softValueTable, 10 * 8);
				char* split = printTable(splitTable, 10 * 10);
				char* surrTable = printTable(surrenderTable, 17 * 10);
				//printf("Hard Values: %s\nSoft Values: %s\nSplit: %s\nSurrender: %s", hvt, svt, split, surrTable);
				Condition* cond = (Condition*)malloc(sizeof(Condition));
				*cond = Condition(1, 1, CmpType::EQ);
				Move* moves = (Move*)malloc(sizeof(Move) * 10 * 17);
				BSTableCell* cells;
				cells = (BSTableCell*)malloc(sizeof(BSTableCell)* 170);
				if (cells == nullptr) {
					break;
				}
				//BSTableCell temp = BSTableCell(cond, moves, 1);
				//std::cout << temp.getCount() << "\n";
				for (int i = 0; i < 17; i++) {
					for (int j = 0; j < 10; j++) {
						switch (hardValueTable[(i * 10 + j)*2]) {
						case 'D': {moves[i * 10 + j] = DOUBLE; } break;
						case 'H': {moves[i * 10 + j] = HIT; } break;
						default: {moves[i * 10 + j] = STAND; } break;
						}
						cells[i * 10 + j] = BSTableCell(cond, (moves + (j + i * 10)), 1);;
					}
				}
				BSTable table = BSTable(cells, 17, 10);
				std::cout << table.toString(objects, 11) << "\n";
			}
			if (ImGui::Button("Set to default")) {
				setTable(hardValueTable, defHvt, 10 * 17);
				setTable(softValueTable, defSvt, 10 * 8);
				setTable(splitTable, defSplit, 10 * 10);
				setTable(surrenderTable, defSurr, 10 * 17);
			}
			ImGui::End();
		}
		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

char* printTable(char* table, int size) {
	char* fixed = (char*)calloc(size, 1);
	int runningIndex = 0;
	for (int i = 0; i < size * 2; i += 2) {
		if (!isalpha(table[i])) {
			fixed[runningIndex++] = ' ';
		}
		else {
			fixed[runningIndex++] = table[i];
		}
	}
	fixed[runningIndex] = '\0';
	return fixed;
}

void makeTable(int rowStart, int rowEnd, std::string idStart, char* table) {
	int id;
	ImGui::TableSetupColumn(" ", ImGuiTableColumnFlags_WidthFixed);
	for (int i = 2; i < 12; i++) {
		ImGui::TableSetupColumn(std::to_string(i).c_str(), ImGuiTableColumnFlags_WidthFixed);
	}
	ImGui::TableHeadersRow();
	for (int i = rowEnd; i > rowStart; i--) {
		ImGui::TableNextColumn();
		ImGui::Text("%d", i);
		for (int j = 2; j < 12; j++) {
			ImGui::TableNextColumn();
			ImGui::SetNextItemWidth(20.0f);
			id = (i - rowStart - 1) * 10 + j - 2;
			ImGui::InputText((idStart + std::to_string(id)).c_str(), table + id * 2, 2, ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_AlwaysOverwrite);
		}
	}
	ImGui::EndTable();
}

void setTable(char* table, char* values, int size) {
	for (int i = 0; i < size * 2; i += 2) {
		table[i] = values[i / 2];
		table[i + 1] = '\0';
	}
}
