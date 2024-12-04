#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Disciplina
{
    string nome;
    vector<double> notas;
    double media;
};

struct Aluno
{
    string nome;
    int matricula;
    vector<Disciplina> disciplinas;
};

void cadastrarAluno(vector<Aluno>& alunos);
void exibirAlunos(const vector<Aluno>& alunos);
void salvarDados(const vector<Aluno>& alunos, const string& nomeArquivo);
void carregarDados(vector<Aluno>& alunos, const string& nomeArquivo);
void pesquisarAluno(const vector<Aluno>& alunos);

int main()
{
    vector<Aluno> alunos;
    string nomeArquivo = "bd_alunos.txt";

    carregarDados(alunos, nomeArquivo);

    int option;

    do
    {
        system("cls");
        cout << "******* Sistema de Cadastro de Alunos *******" << endl;
        cout << "1. Cadastrar Aluno" << endl;
        cout << "2. Exibir Alunos Cadastrados" << endl;
        cout << "3. Pesquisar por Aluno" << endl;
        cout << "4. Salvar Dados dos Alunos" << endl;
        cout << "5. Sair da aplicacao" << endl;
        cout << "Informe a sua escolha: ";
        cin >> option;

        switch (option)
        {
        case 1:
            cadastrarAluno(alunos);
            system("pause");
            break;
        case 2:
            exibirAlunos(alunos);
            system("pause");
            break;
        case 3:
            pesquisarAluno(alunos);
            system("pause");
            break;
        case 4:
            salvarDados(alunos, nomeArquivo);
            cout << "Dados salvos com sucesso." << endl;
            system("pause");
            break;
        case 5:
            cout << "Encerrado a aplicacao..." << endl;
            break;
        default:
            cout << "Opcao Invalida, tente novamente." << endl;
            break;
        }
    } while (option != 5);
    system("pause");
    return 0;
}


void cadastrarAluno(vector<Aluno>& alunos){
    Aluno novoAluno;
    cout << "******* Cadastrar Aluno ********" << endl;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, novoAluno.nome);

    cout << "Matricula: ";
    cin >> novoAluno.matricula;

    int qtdDisciplinas = 0;
    cout << "Quantas disciplinas o aluno estara se matriculando: ";
    cin >> qtdDisciplinas;

    novoAluno.disciplinas.resize(qtdDisciplinas);
    //novoAluno.notas.resize(qtdDisciplinas * 2)

    cin.ignore();
    double nota, somaNotas = 0.0;

    for (int i = 0; i < qtdDisciplinas; i++)
    {
        cout << "Nome da Disciplina " << i+1 << ": ";
        //getline(cin, novoAluno.disciplinas[i].nome);
        cin >> novoAluno.disciplinas[i].nome;

        for (int j = 0; j < 2; j++)
        {
            cout << "Informe a Nota " << j+1 << ": ";
            cin >> nota;
            novoAluno.disciplinas[i].notas.push_back(nota);
            somaNotas += nota;
        }
        
        novoAluno.disciplinas[i].media = somaNotas / 2.0;
        somaNotas = 0.0;
    }
    
    alunos.push_back(novoAluno);
    cout << "Aluno cadastrado com sucesso!" << endl;
}

void salvarDados(const vector<Aluno>& alunos, const string& nomeArquivo){
    ofstream arquivo(nomeArquivo);

    if(!arquivo.is_open()){
        cerr << "Erro ao abrir o arquivo de dados." << endl;
        return;
    }

    for (const auto& aluno : alunos)
    {
        arquivo << aluno.nome << endl;
        arquivo << aluno.matricula << endl;
        arquivo << aluno.disciplinas.size() << endl;

        for (const auto& disciplina : aluno.disciplinas)
        {
            arquivo << disciplina.nome << endl;
            for (const auto& nota : disciplina.notas)
            {
                arquivo << nota << " ";
            }
            arquivo << endl;
            arquivo << disciplina.media << endl;
        
        }

    }

    arquivo.close();
    
}

void carregarDados(vector<Aluno>& alunos, const string& nomeArquivo){
    ifstream arquivo(nomeArquivo);

    if(!arquivo.is_open()){
        cerr << "Erro ao abrir o arquivo de dados." << endl;
        return;
    }

    while (!arquivo.eof())
    {
        Aluno aluno;
        if(!getline(arquivo,aluno.nome)) break;
        arquivo >> aluno.matricula;

        int qtdDisciplinas;
        arquivo >> qtdDisciplinas;
        arquivo.ignore();

        aluno.disciplinas.resize(qtdDisciplinas);

        for (int i = 0; i < qtdDisciplinas; i++)
        {
            getline(arquivo, aluno.disciplinas[i].nome);

            aluno.disciplinas[i].notas.resize(2);
            for (int j = 0; j < 2; j++)
            {
                arquivo >> aluno.disciplinas[i].notas[j];
            }
            arquivo >> aluno.disciplinas[i].media;
            arquivo.ignore();
        }
        alunos.push_back(aluno);
    }
    arquivo.close();
    cout << "Dados carregados com sucesso!" << endl;
}

void exibirAlunos(const vector<Aluno>& alunos){
    cout << "" << endl;

    if (alunos.empty())
    {
        cout << "Atenção Nenhum aluno cadastrado." << endl;
        return;
    }
    
    cout << "" << endl;
    for (const auto& aluno : alunos)
    {
        cout << "Nome do Aluno: " << aluno.nome << endl;
        cout << "Matricula: " << aluno.matricula << endl;

        cout << "-----Disciplinas e Notas ------" << endl;
        for (const auto& disciplina : aluno.disciplinas)
        {
            cout << "# " << disciplina.nome << " - Notas: ";
            for (const auto& nota : disciplina.notas)
            {
                cout << fixed << setprecision(2) << nota << " ";
            }
            cout << " ." << endl;
            cout << "    Media: " << fixed << setprecision(2) << disciplina.media << endl;

        }
        cout << "_________________________________________" << endl;
    }
    
}

void pesquisarAluno(const vector<Aluno>& alunos){
    int matricula;
    cout << "Informe a Matricula do Aluno: ";
    cin >> matricula;

    for (const auto& aluno : alunos)
    {
        if (aluno.matricula == matricula)
        {
            cout << "Aluno localizado com sucesso!" << endl;
            cout << "Nome do Aluno: " << aluno.nome << endl;
            cout << "Matricula: " << aluno.matricula << endl;

            cout << "-----Disciplinas e Notas ------" << endl;
            for (const auto& disciplina : aluno.disciplinas)
            {
                cout << "# " << disciplina.nome << " - Notas: ";
                for (const auto& nota : disciplina.notas)
                {
                    cout << fixed << setprecision(2) << nota << " ";
                }
                cout << " ." << endl;
                cout << "    Media: " << fixed << setprecision(2) << disciplina.media << endl;

            }
            return;
        }
        
    }

    cout << "Aluno nao encontrado." << endl;
    
}

//CREATE READ UPDATE DELETE