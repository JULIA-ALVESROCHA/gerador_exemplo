/**
 * Sistema de Gestão de Imóveis - Versão Completa
 * Júlia Alves da Rocha - 2025.1.08.015
 * Versão para estudantes do primeiro período
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// Estrutura do imóvel
struct Imovel {
    string tipo;           // Casa, Apartamento, Comercial
    string finalidade;     // Venda, Aluguel, Temporada
    string endereco;
    string rua;           // Campo específico para busca
    string cidade;
    double area;
    double valor;
    int quartos;
    int suites;           // Número de suítes
    int banheiros;
    string conservacao;   // Novo, Usado, Reformado
    
    // Características adicionais
    bool armarios;
    bool arCondicionado;
    bool aquecedor;
    bool ventilador;
    bool ceramicaSala;    // Para salas comerciais
};

// Variáveis globais
vector<Imovel> imoveis;
const string ARQUIVO = "imoveis.txt";

// Protótipos das funções
void mostrarMenu();
void incluirImovel();
void listarImoveis();
void buscarPorRua();
void buscarPorValor();
void buscarPorCaracteristicas();
void buscarPorQuartosSuites();
void relatorioEstatisticas();
void excluirImovel();
void salvarArquivo();
void carregarArquivo();
void limparTela();
void pausar();

int main() {
    cout << "=== Sistema de Gestao de Imoveis ===" << endl;
    cout << "Carregando dados..." << endl;
    carregarArquivo();
    
    int opcao;
    do {
        mostrarMenu();
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        
        switch(opcao) {
            case 1:
                incluirImovel();
                break;
            case 2:
                listarImoveis();
                break;
            case 3:
                buscarPorRua();
                break;
            case 4:
                buscarPorValor();
                break;
            case 5:
                buscarPorCaracteristicas();
                break;
            case 6:
                buscarPorQuartosSuites();
                break;
            case 7:
                relatorioEstatisticas();
                break;
            case 0:
                cout << "Salvando dados..." << endl;
                salvarArquivo();
                cout << "Programa encerrado!" << endl;
                break;
            default:
                cout << "Opcao invalida!" << endl;
                pausar();
        }
    } while(opcao != 0);
    
    return 0;
}

void mostrarMenu() {
    limparTela();
    cout << "================================" << endl;
    cout << "   SISTEMA DE GESTAO DE IMOVEIS" << endl;
    cout << "================================" << endl;
    cout << "1. Incluir Imovel" << endl;
    cout << "2. Listar Todos os Imoveis" << endl;
    cout << "3. Buscar por Rua (com opcao de exclusao)" << endl;
    cout << "4. Buscar por Faixa de Valor" << endl;
    cout << "5. Buscar por Caracteristicas" << endl;
    cout << "6. Buscar por Quartos e Suites" << endl;
    cout << "7. Relatorio de Estatisticas" << endl;
    cout << "0. Sair" << endl;
    cout << "================================" << endl;
    cout << "Total de imoveis: " << imoveis.size() << endl;
    cout << "================================" << endl;
}

void incluirImovel() {
    limparTela();
    cout << "=== INCLUIR NOVO IMOVEL ===" << endl;
    
    Imovel novo;
    char resposta;
    
    cout << "Tipo (Casa/Apartamento/Comercial): ";
    cin.ignore();
    getline(cin, novo.tipo);
    
    cout << "Finalidade (Venda/Aluguel/Temporada): ";
    getline(cin, novo.finalidade);
    
    cout << "Endereco completo: ";
    getline(cin, novo.endereco);
    
    cout << "Rua: ";
    getline(cin, novo.rua);
    
    cout << "Cidade: ";
    getline(cin, novo.cidade);
    
    cout << "Area (m²): ";
    cin >> novo.area;
    
    cout << "Valor (R$): ";
    cin >> novo.valor;
    
    cout << "Numero de quartos: ";
    cin >> novo.quartos;
    
    cout << "Numero de suites: ";
    cin >> novo.suites;
    
    cout << "Numero de banheiros: ";
    cin >> novo.banheiros;
    
    cout << "Conservacao (Novo/Usado/Reformado): ";
    cin.ignore();
    getline(cin, novo.conservacao);
    
    // Características adicionais
    cout << "\n--- CARACTERISTICAS ---" << endl;
    
    cout << "Possui armarios? (s/n): ";
    cin >> resposta;
    novo.armarios = (resposta == 's' || resposta == 'S');
    
    cout << "Possui ar-condicionado? (s/n): ";
    cin >> resposta;
    novo.arCondicionado = (resposta == 's' || resposta == 'S');
    
    cout << "Possui aquecedor? (s/n): ";
    cin >> resposta;
    novo.aquecedor = (resposta == 's' || resposta == 'S');
    
    cout << "Possui ventilador? (s/n): ";
    cin >> resposta;
    novo.ventilador = (resposta == 's' || resposta == 'S');
    
    // Pergunta sobre cerâmica apenas para imóveis comerciais
    string tipoLower = novo.tipo;
    transform(tipoLower.begin(), tipoLower.end(), tipoLower.begin(), ::tolower);
    if(tipoLower.find("comercial") != string::npos) {
        cout << "Sala possui piso ceramico? (s/n): ";
        cin >> resposta;
        novo.ceramicaSala = (resposta == 's' || resposta == 'S');
    } else {
        novo.ceramicaSala = false;
    }
    
    imoveis.push_back(novo);
    cout << endl << "Imovel incluido com sucesso!" << endl;
    pausar();
}

void listarImoveis() {
    limparTela();
    if(imoveis.empty()) {
        cout << "Nenhum imovel cadastrado!" << endl;
        pausar();
        return;
    }
    
    cout << "=== LISTA DE TODOS OS IMOVEIS DISPONIVEIS ===" << endl;
    
    for(size_t i = 0; i < imoveis.size(); i++) {
        cout << "\n--- Imovel " << (i+1) << " ---" << endl;
        cout << "Tipo: " << imoveis[i].tipo << endl;
        cout << "Finalidade: " << imoveis[i].finalidade << endl;
        cout << "Endereco: " << imoveis[i].endereco << endl;
        cout << "Rua: " << imoveis[i].rua << endl;
        cout << "Cidade: " << imoveis[i].cidade << endl;
        cout << "Area: " << imoveis[i].area << " m²" << endl;
        cout << "Valor: R$ " << fixed << setprecision(2) << imoveis[i].valor << endl;
        cout << "Quartos: " << imoveis[i].quartos << " | Suites: " << imoveis[i].suites << endl;
        cout << "Banheiros: " << imoveis[i].banheiros << endl;
        cout << "Conservacao: " << imoveis[i].conservacao << endl;
        
        cout << "Caracteristicas: ";
        if(imoveis[i].armarios) cout << "Armarios ";
        if(imoveis[i].arCondicionado) cout << "Ar-condicionado ";
        if(imoveis[i].aquecedor) cout << "Aquecedor ";
        if(imoveis[i].ventilador) cout << "Ventilador ";
        if(imoveis[i].ceramicaSala) cout << "Piso-ceramico ";
        cout << endl;
    }
    pausar();
}

void buscarPorRua() {
    limparTela();
    if(imoveis.empty()) {
        cout << "Nenhum imovel cadastrado!" << endl;
        pausar();
        return;
    }
    
    cout << "=== BUSCAR POR RUA ===" << endl;
    string rua;
    
    cout << "Digite o nome da rua: ";
    cin.ignore();
    getline(cin, rua);
    
    vector<int> encontrados;
    cout << "\nImoveis encontrados na rua " << rua << ":" << endl;
    
    for(size_t i = 0; i < imoveis.size(); i++) {
        string ruaImovel = imoveis[i].rua;
        transform(ruaImovel.begin(), ruaImovel.end(), ruaImovel.begin(), ::tolower);
        transform(rua.begin(), rua.end(), rua.begin(), ::tolower);
        
        if(ruaImovel.find(rua) != string::npos) {
            cout << "\n--- Imovel " << (i+1) << " ---" << endl;
            cout << "Tipo: " << imoveis[i].tipo << endl;
            cout << "Endereco: " << imoveis[i].endereco << endl;
            cout << "Valor: R$ " << fixed << setprecision(2) << imoveis[i].valor << endl;
            encontrados.push_back(i);
        }
    }
    
    if(encontrados.empty()) {
        cout << "Nenhum imovel encontrado nesta rua!" << endl;
        pausar();
        return;
    }
    
    // Opção de exclusão
    cout << "\nDeseja excluir algum imovel? (s/n): ";
    char resposta;
    cin >> resposta;
    
    if(resposta == 's' || resposta == 'S') {
        cout << "Digite o numero do imovel para excluir: ";
        int numero;
        cin >> numero;
        
        if(numero >= 1 && numero <= (int)imoveis.size()) {
            imoveis.erase(imoveis.begin() + numero - 1);
            cout << "Imovel excluido com sucesso!" << endl;
        } else {
            cout << "Numero invalido!" << endl;
        }
    }
    pausar();
}

void buscarPorValor() {
    limparTela();
    if(imoveis.empty()) {
        cout << "Nenhum imovel cadastrado!" << endl;
        pausar();
        return;
    }
    
    cout << "=== BUSCAR POR FAIXA DE VALOR ===" << endl;
    double valorMin, valorMax;
    string finalidade;
    
    cout << "Finalidade (Venda/Aluguel/Temporada ou ENTER para todas): ";
    cin.ignore();
    getline(cin, finalidade);
    
    cout << "Valor minimo (R$): ";
    cin >> valorMin;
    cout << "Valor maximo (R$): ";
    cin >> valorMax;
    
    cout << "\nImoveis encontrados:" << endl;
    bool encontrou = false;
    
    for(size_t i = 0; i < imoveis.size(); i++) {
        bool valorOk = (imoveis[i].valor >= valorMin && imoveis[i].valor <= valorMax);
        bool finalidadeOk = finalidade.empty() || 
                           (imoveis[i].finalidade.find(finalidade) != string::npos);
        
        if(valorOk && finalidadeOk) {
            cout << "\n--- Imovel " << (i+1) << " ---" << endl;
            cout << "Tipo: " << imoveis[i].tipo << endl;
            cout << "Finalidade: " << imoveis[i].finalidade << endl;
            cout << "Endereco: " << imoveis[i].endereco << endl;
            cout << "Valor: R$ " << fixed << setprecision(2) << imoveis[i].valor << endl;
            encontrou = true;
        }
    }
    
    if(!encontrou) {
        cout << "Nenhum imovel encontrado nos criterios especificados!" << endl;
    }
    pausar();
}

void buscarPorCaracteristicas() {
    limparTela();
    if(imoveis.empty()) {
        cout << "Nenhum imovel cadastrado!" << endl;
        pausar();
        return;
    }
    
    cout << "=== BUSCAR POR CARACTERISTICAS ===" << endl;
    cout << "Marque as caracteristicas desejadas:" << endl;
    
    bool buscaArmarios = false, buscaAr = false, buscaAquecedor = false, buscaVentilador = false;
    char resposta;
    
    cout << "Armarios? (s/n): ";
    cin >> resposta;
    buscaArmarios = (resposta == 's' || resposta == 'S');
    
    cout << "Ar-condicionado? (s/n): ";
    cin >> resposta;
    buscaAr = (resposta == 's' || resposta == 'S');
    
    cout << "Aquecedor? (s/n): ";
    cin >> resposta;
    buscaAquecedor = (resposta == 's' || resposta == 'S');
    
    cout << "Ventilador? (s/n): ";
    cin >> resposta;
    buscaVentilador = (resposta == 's' || resposta == 'S');
    
    cout << "\nImoveis encontrados:" << endl;
    bool encontrou = false;
    
    for(size_t i = 0; i < imoveis.size(); i++) {
        bool match = true;
        
        if(buscaArmarios && !imoveis[i].armarios) match = false;
        if(buscaAr && !imoveis[i].arCondicionado) match = false;
        if(buscaAquecedor && !imoveis[i].aquecedor) match = false;
        if(buscaVentilador && !imoveis[i].ventilador) match = false;
        
        if(match) {
            cout << "\n--- Imovel " << (i+1) << " ---" << endl;
            cout << "Tipo: " << imoveis[i].tipo << endl;
            cout << "Endereco: " << imoveis[i].endereco << endl;
            cout << "Valor: R$ " << fixed << setprecision(2) << imoveis[i].valor << endl;
            cout << "Caracteristicas: ";
            if(imoveis[i].armarios) cout << "Armarios ";
            if(imoveis[i].arCondicionado) cout << "Ar-condicionado ";
            if(imoveis[i].aquecedor) cout << "Aquecedor ";
            if(imoveis[i].ventilador) cout << "Ventilador ";
            cout << endl;
            encontrou = true;
        }
    }
    
    if(!encontrou) {
        cout << "Nenhum imovel encontrado com essas caracteristicas!" << endl;
    }
    pausar();
}

void buscarPorQuartosSuites() {
    limparTela();
    if(imoveis.empty()) {
        cout << "Nenhum imovel cadastrado!" << endl;
        pausar();
        return;
    }
    
    cout << "=== BUSCAR POR QUARTOS E SUITES ===" << endl;
    int minQuartos, minSuites;
    
    cout << "Numero minimo de quartos: ";
    cin >> minQuartos;
    cout << "Numero minimo de suites: ";
    cin >> minSuites;
    
    cout << "\nImoveis encontrados:" << endl;
    bool encontrou = false;
    
    for(size_t i = 0; i < imoveis.size(); i++) {
        if(imoveis[i].quartos >= minQuartos && imoveis[i].suites >= minSuites) {
            cout << "\n--- Imovel " << (i+1) << " ---" << endl;
            cout << "Tipo: " << imoveis[i].tipo << endl;
            cout << "Endereco: " << imoveis[i].endereco << endl;
            cout << "Valor: R$ " << fixed << setprecision(2) << imoveis[i].valor << endl;
            cout << "Quartos: " << imoveis[i].quartos << " | Suites: " << imoveis[i].suites << endl;
            encontrou = true;
        }
    }
    
    if(!encontrou) {
        cout << "Nenhum imovel encontrado com esses criterios!" << endl;
    }
    pausar();
}

void relatorioEstatisticas() {
    limparTela();
    if(imoveis.empty()) {
        cout << "Nenhum imovel cadastrado!" << endl;
        pausar();
        return;
    }
    
    cout << "=== RELATORIO DE ESTATISTICAS ===" << endl;
    
    // Contadores
    int totalImoveis = imoveis.size();
    int vendas = 0, alugueis = 0, temporadas = 0;
    int casas = 0, casasComSuites = 0;
    int comerciais = 0, comerciaisCeramica = 0;
    
    for(const auto& imovel : imoveis) {
        // Finalidades
        string finalidade = imovel.finalidade;
        transform(finalidade.begin(), finalidade.end(), finalidade.begin(), ::tolower);
        
        if(finalidade.find("venda") != string::npos) vendas++;
        else if(finalidade.find("aluguel") != string::npos) alugueis++;
        else if(finalidade.find("temporada") != string::npos) temporadas++;
        
        // Casas com suítes
        string tipo = imovel.tipo;
        transform(tipo.begin(), tipo.end(), tipo.begin(), ::tolower);
        
        if(tipo.find("casa") != string::npos) {
            casas++;
            if(imovel.suites > 0) casasComSuites++;
        }
        
        // Comerciais com cerâmica
        if(tipo.find("comercial") != string::npos) {
            comerciais++;
            if(imovel.ceramicaSala) comerciaisCeramica++;
        }
    }
    
    cout << "\n--- PORCENTAGENS POR FINALIDADE ---" << endl;
    cout << "Vendas: " << fixed << setprecision(1) 
         << (totalImoveis > 0 ? (vendas * 100.0 / totalImoveis) : 0) << "%" << endl;
    cout << "Alugueis: " << fixed << setprecision(1) 
         << (totalImoveis > 0 ? (alugueis * 100.0 / totalImoveis) : 0) << "%" << endl;
    cout << "Temporadas: " << fixed << setprecision(1) 
         << (totalImoveis > 0 ? (temporadas * 100.0 / totalImoveis) : 0) << "%" << endl;
    
    cout << "\n--- CASAS COM SUITES ---" << endl;
    cout << "Casas com suites: " << fixed << setprecision(1) 
         << (casas > 0 ? (casasComSuites * 100.0 / casas) : 0) << "%" << endl;
    cout << "(" << casasComSuites << " de " << casas << " casas)" << endl;
    
    cout << "\n--- SALAS COMERCIAIS COM CERAMICA ---" << endl;
    cout << "Comerciais com piso ceramico: " << fixed << setprecision(1) 
         << (comerciais > 0 ? (comerciaisCeramica * 100.0 / comerciais) : 0) << "%" << endl;
    cout << "(" << comerciaisCeramica << " de " << comerciais << " comerciais)" << endl;
    
    cout << "\n--- RESUMO GERAL ---" << endl;
    cout << "Total de imoveis: " << totalImoveis << endl;
    
    pausar();
}

void excluirImovel() {
    limparTela();
    if(imoveis.empty()) {
        cout << "Nenhum imovel cadastrado!" << endl;
        pausar();
        return;
    }
    
    cout << "=== EXCLUIR IMOVEL ===" << endl;
    
    for(size_t i = 0; i < imoveis.size(); i++) {
        cout << i+1 << ". " << imoveis[i].tipo << " - " 
             << imoveis[i].endereco << " - R$ " 
             << fixed << setprecision(2) << imoveis[i].valor << endl;
    }
    
    int numero;
    cout << "\nDigite o numero do imovel para excluir (0 para cancelar): ";
    cin >> numero;
    
    if(numero == 0) {
        cout << "Operacao cancelada!" << endl;
    }
    else if(numero < 1 || numero > (int)imoveis.size()) {
        cout << "Numero invalido!" << endl;
    }
    else {
        imoveis.erase(imoveis.begin() + numero - 1);
        cout << "Imovel excluido com sucesso!" << endl;
    }
    pausar();
}

void salvarArquivo() {
    ofstream arquivo(ARQUIVO);
    if(!arquivo.is_open()) {
        cout << "Erro ao salvar arquivo!" << endl;
        return;
    }
    
    for(const auto& imovel : imoveis) {
        arquivo << imovel.tipo << "|"
                << imovel.finalidade << "|"
                << imovel.endereco << "|"
                << imovel.rua << "|"
                << imovel.cidade << "|"
                << imovel.area << "|"
                << imovel.valor << "|"
                << imovel.quartos << "|"
                << imovel.suites << "|"
                << imovel.banheiros << "|"
                << imovel.conservacao << "|"
                << imovel.armarios << "|"
                << imovel.arCondicionado << "|"
                << imovel.aquecedor << "|"
                << imovel.ventilador << "|"
                << imovel.ceramicaSala << endl;
    }
    arquivo.close();
}

void carregarArquivo() {
    ifstream arquivo(ARQUIVO);
    if(!arquivo.is_open()) {
        cout << "Arquivo nao encontrado. Iniciando sistema vazio." << endl;
        return;
    }
    
    string linha;
    while(getline(arquivo, linha)) {
        Imovel imovel;
        size_t pos = 0;
        size_t found = 0;
        
        // Parsing usando delimitador |
        found = linha.find('|', pos);
        imovel.tipo = linha.substr(pos, found - pos);
        pos = found + 1;
        
        found = linha.find('|', pos);
        imovel.finalidade = linha.substr(pos, found - pos);
        pos = found + 1;
        
        found = linha.find('|', pos);
        imovel.endereco = linha.substr(pos, found - pos);
        pos = found + 1;
        
        found = linha.find('|', pos);
        imovel.rua = linha.substr(pos, found - pos);
        pos = found + 1;
        
        found = linha.find('|', pos);
        imovel.cidade = linha.substr(pos, found - pos);
        pos = found + 1;
        
        found = linha.find('|', pos);
        imovel.area = stod(linha.substr(pos, found - pos));
        pos = found + 1;
        
        found = linha.find('|', pos);
        imovel.valor = stod(linha.substr(pos, found - pos));
        pos = found + 1;
        
        found = linha.find('|', pos);
        imovel.quartos = stoi(linha.substr(pos, found - pos));
        pos = found + 1;
        
        found = linha.find('|', pos);
        imovel.suites = stoi(linha.substr(pos, found - pos));
        pos = found + 1;
        
        found = linha.find('|', pos);
        imovel.banheiros = stoi(linha.substr(pos, found - pos));
        pos = found + 1;
        
        found = linha.find('|', pos);
        imovel.conservacao = linha.substr(pos, found - pos);
        pos = found + 1;
        
        found = linha.find('|', pos);
        imovel.armarios = (linha.substr(pos, found - pos) == "1");
        pos = found + 1;
        
        found = linha.find('|', pos);
        imovel.arCondicionado = (linha.substr(pos, found - pos) == "1");
        pos = found + 1;
        
        found = linha.find('|', pos);
        imovel.aquecedor = (linha.substr(pos, found - pos) == "1");
        pos = found + 1;
        
        found = linha.find('|', pos);
        imovel.ventilador = (linha.substr(pos, found - pos) == "1");
        pos = found + 1;
        
        imovel.ceramicaSala = (linha.substr(pos) == "1");
        
        imoveis.push_back(imovel);
    }
    arquivo.close();
    cout << "Carregados " << imoveis.size() << " imoveis do arquivo." << endl;
}

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    cout << "\nPressione ENTER para continuar...";
    cin.ignore();
    cin.get();
}
