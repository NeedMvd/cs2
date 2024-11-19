// CS2 BAIMLESS.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "Memory/Memory.h"
#include "Offsets/Offsets.h"
#include "Menu/Menu.h"
#include "ImGui/OS-ImGui.h"
#include "Cheat/SDK/Game.h"
template <typename... Args>
inline std::string Format(const char* pFormat, Args...args)
{
	int Length = std::snprintf(nullptr, 0, pFormat, args...);
	if (Length <= 0)
		return "";
	char* Str = new char[Length + 1];
	std::string Result;
	std::snprintf(Str, Length + 1, pFormat, args...);
	Result = std::string(Str);
	delete[] Str;
	return Result;
}

int main()
{
	auto ProcessStatus = ProcessMgr.Attach("cs2.exe");

	if (ProcessStatus != StatusCode::SUCCEED)
	{
		std::cout << "[ERROR] Failed to attach process, StatusCode:" << ProcessStatus << std::endl;
	}

	if (!Offset::UpdateOffsets())
	{
		std::cout << "[ERROR] Failed to update offsets." << std::endl;
	}
	std::cout << Format("[Game] Pid:%d\n", ProcessMgr.ProcessID);
	
	if (!gGame.InitAddress())
	{
		std::cout << "[ERROR] Failed to call InitAddress()." << std::endl;
	}

	std::cout << "Offset:" << std::endl;
	std::cout << Format("--EntityList:%llX\n", Offset::client_dll.dwEntityList);
	std::cout << Format("--Matrix:%llX\n", Offset::client_dll.dwViewMatrix);
	std::cout << Format("--LocalPlayerController:%llX\n", Offset::client_dll.dwLocalPlayerController);
	std::cout << Format("--ViewAngles:%llX\n", Offset::client_dll.dwViewAngles);	

	try
	{
		Gui.AttachAnotherWindow("Counter-Strike 2", "SDL_app", Menu::Draw);
	}
	catch (OSImGui::OSException& e)
	{
		std::cout << e.what() << std::endl;
	}
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
