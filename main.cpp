#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 
using namespace std;

class Candidato {
  public:
    string partido;   
    string nome;
    string numero;

};

void tokenize(std::string const &str, const char delim,std::vector<std::string> &out){
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

 vector<Candidato> read_file(){
    string path_file_name = "base.txt";
    std::ifstream file(path_file_name);
    const char delim = ',';
    std::vector<std::string> out;

    vector<Candidato> candidatos;

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            // using printf() in all tests for consistency
            tokenize(line.c_str(), delim, out);
        }
        file.close();
    }
    for(int i=0;i<out.size();i++){
        Candidato candidato;
        candidato.partido =  out[i];
        candidato.nome = out[i+1];
        candidato.numero = out[i+2];
        candidatos.push_back(candidato);
    }
    return candidatos;
}


Candidato find_candidato(vector<Candidato> candidatos, string numero){
    Candidato candidato;
    candidato.numero = "000";
    for(int i=0;i<candidatos.size();i++){
        if(candidatos[i].numero == numero){
            candidato = candidatos[i];
        }
    }
    return candidato;
}

void salvar_voto(string numero){
    string path_file_name = "votos.txt";
    ofstream outfile;
    outfile.open(path_file_name, ios::app);
    outfile << numero << endl;
    outfile.close();
}

void salvar_votacao(string nome, string numero,float porcentagem,int votos_candidato){
    string path_file_name = "votacao.txt";
    ofstream outfile;
    outfile.open(path_file_name, ios::app);
    outfile << nome <<" (" << numero <<") : " << porcentagem << " % " << votos_candidato  << " votos"<< endl;
    outfile.close();
}

void opcao_1(vector<Candidato> candidatos){
    
    string numero = "";
    string voto = "";
    std::cout << "Informe o numero do seu candidato " << std::endl;
    std::cin >> numero;
    Candidato candidato = find_candidato(candidatos, numero);
    if(candidato.numero != "000"){
        std::cout <<"Numero do candidato: " << candidato.numero << endl;
        std::cout << "Nome: "<< candidato.nome << endl;
        std::cout << "Partido: " << candidato.partido << endl;
    }else{
        std::cout << "Candidato nao encontrado" <<endl;
    }
    std::cout << "Confirma o voto(S/N)? ";
    std::cin >> voto;
    if(voto == "S"){
        if(candidato.numero == "000"){
            std::cout << "voto branco salvo" << endl;
        }else{
           std::cout << "voto salvo" << endl;
        }
        salvar_voto(candidato.numero);
    }
}

void opcao(vector<Candidato> candidatos, int opcao){
    string path_file_name = "votos.txt";
    std::ifstream file(path_file_name);
    std::vector<std::string> votos;
    std::vector<std::string> votos_total;
    int total_votos;

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            votos.push_back(line.c_str());
        }
        file.close();
    }

    votos_total = votos;
    total_votos = votos_total.size();
    //eleminando as duplicatas
    std::sort(votos.begin(), votos.end() );
    votos.erase(unique( votos.begin(), votos.end() ), votos.end() );

    
    //criando lista de
    for(int i = 0;i<votos.size();i++){
        int votos_candidato = 0;
        float porcentagem = 0.0;
        Candidato candidato = find_candidato(candidatos, votos[i]);
        if(candidato.numero == "000"){
            for(int j = 0;j<votos_total.size();j++){
                if(candidato.numero == votos_total[j]){
                    votos_candidato+=1;
                }
            }
            porcentagem = (100*votos_candidato)/total_votos; 
            if(opcao == 3){
                salvar_votacao("Votos brancos",candidato.numero,porcentagem,votos_candidato);
            }else{
                std::cout << "Votos brancos" <<" (" << candidato.numero <<") : " << porcentagem << " % " << votos_candidato  << " votos"<< endl;
            }
        }else{
            for(int j = 0;j<votos_total.size();j++){
                if(candidato.numero == votos_total[j]){
                    votos_candidato+=1;
                }
            }
            porcentagem = (100*votos_candidato)/total_votos;
            if(opcao == 3){
                salvar_votacao(candidato.nome,candidato.numero,porcentagem,votos_candidato);
            }else{
                std::cout << candidato.nome <<" (" << candidato.numero <<") : " << porcentagem << " % " << votos_candidato  << " votos"<< endl;
            }
        }
    }

}

int main( int argc, char * argv[] ){
    vector<Candidato> candidatos = read_file();

    int op = 0;
    while(op != 4){
        std::cout << "1 - Registrar voto" << std::endl;
        std::cout << "2 - Exibir resultado parcial" << std::endl;
        std::cout << "3 - Imprimir resultado de votacao" << std::endl;
        std::cout << "4 - Sair" << std::endl;
        std::cin >> op;
        switch(op){
            case 1:
                opcao_1(candidatos);
            break;
            case 2:
                opcao(candidatos, 2);
            break;
            case 3:
                opcao(candidatos, 3);
            break;
            case 4:
                exit(1);
            break;
        }
    }
    return 0;
}