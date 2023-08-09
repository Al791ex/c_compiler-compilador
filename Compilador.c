#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool verificar_variables(char variable[50]){
    int v_longitud = strlen(variable);
    bool status_variable;
    for (int i = 0; i < v_longitud; i++){
        if (!isalpha(variable[i])){
            status_variable = false;
            break;
        } else {
            status_variable = true;
        }
    }
    return status_variable;
}

bool verificar_num(char array_tokens[50]){
    int n_longitud = strlen(array_tokens);
    bool status_num;
    int index = 0;

    if (array_tokens[0] == '-'){
        index = 1;
    }
    for (int i = index; i < n_longitud; i++) {
            if (array_tokens[i] != '.'){
                if (!isdigit(array_tokens[i])) {
                    status_num = false;
                    break;
                }else{
                    status_num = true;
                } 
            }else{
                status_num = true;
            }  
        }
    return status_num;
}

bool verificar_dato(char array_tokens[50]){
    bool status_dato = false;
    char tipos_datos[][7] = {"int","float","char","string"};
    for(int i = 0; i <=4; i++){
        if (strcmp(array_tokens, tipos_datos[i]) == 0){
            status_dato = true;
            break;
        }
    }

    return status_dato;
}

bool verificar_operador_comparacion(char array_tokens[50]){
    char operadores_comparacion[][3] = {"==","<",">","!=",">=","<="};
    bool status_operador = false;
    for (int i = 0; i <=6; i++){
        if (strcmp(array_tokens,operadores_comparacion[i]) == 0){
            status_operador = true;
            break;
        }else{
            status_operador = false;
        }
    }

    return status_operador;
}

bool verificar_operador_doble(char array_tokens[50]){
    char operadores[][3] = {"++","--"};
    bool status_operador = false;
    for (int i = 0; i <= 2; i++){
        if (strcmp(array_tokens,operadores[i]) == 0){
            status_operador = true;
            break;
        }else{
            status_operador = false;
        }
    }

    return status_operador;

}
bool verificar_operador(char array_tokens[50]){
    char operadores[][3] = {"+","-","*","/"};
    bool status_operador = false;
    for (int i = 0; i <= 4; i++){
        if (strcmp(array_tokens,operadores[i]) == 0){
            status_operador = true;
            break;
        }else{
            status_operador = false;
        }
    }

    return status_operador;
}

bool verificar_variable_valor(char variable_valor[50],char array_tokens_dato[50]){
    char tipos_datos[][7] = {"int","float","string","char"};
    bool status_variable_valor = false;
    
    if ((strcmp(array_tokens_dato,tipos_datos[0]) == 0 ) || (strcmp(array_tokens_dato,tipos_datos[1]) == 0)){
        status_variable_valor = verificar_num(variable_valor);

    }else if ((strcmp(array_tokens_dato,tipos_datos[2]) == 0) || (strcmp(array_tokens_dato,tipos_datos[3]) == 0)){
        int v_longitud = strlen(variable_valor);
        
        if ((variable_valor[0] == '"' && variable_valor[v_longitud-1] == '"') || ( variable_valor[0] == '\'' && variable_valor[v_longitud-1] == '\'')){
            for (int i = 1; i < v_longitud-1; i++){
                if (!isalpha(variable_valor[i])){
                    status_variable_valor = false;
                    break;
                }else{
                    status_variable_valor = true;
                }
            }

            if (v_longitud > 3 && (strcmp(array_tokens_dato,tipos_datos[3]) == 0)){
                status_variable_valor = false;
            }
            
        }else{
            status_variable_valor = false;
        }  
    }

    return status_variable_valor;
}

int main(){

    char operadores[][3] = {"=","+","-"};
    char estructuras[][6] = {"for", "while", "if"};
    const char separadores[] = " \t\n(){}";
    const char separadores_linea[] = ";{";

    int caso;
    char variable[50];
    char variable_valor[50];
    char string[100];

    printf("---Compilador---\n");
    printf("\nIngresa la expresion a evaluar: ");
    fgets(string,sizeof(string), stdin);

    //LINEAS
    char*token_linea = strtok(string,separadores_linea);
    char *array_token_linea[100];
    int contador_linea = 0;

    while (token_linea != NULL){
        array_token_linea[contador_linea] = token_linea;
        contador_linea++;
        token_linea = strtok(NULL,separadores_linea);
    }

    for (int i = 0; i<contador_linea; i++){

        printf("Linea %d: %s\n", i+1,array_token_linea[i]);
    }

    //TOKENS
    for (int i = 0; i < contador_linea; i++){
        char *token = strtok(array_token_linea[i],separadores);
        char *array_tokens[100];
        int contador = 0;

        while (token != NULL){
            array_tokens[contador] = token;
            contador++;
            token = strtok(NULL,separadores);
        }
        for (int j = 0; j<contador; j++){

            printf("Token %d: %s\n", j,array_tokens[j]);

            if (j+1 == contador){
                printf("\n");

                // Variables
                bool status_dato = false;
                bool status_variable = false;
                bool status_operador = false;
                bool status_num = false;
                bool status_variable_valor = false;
                bool status_declaracion_variable = false;
                bool operador_comparacion = false;
                
                // Estructura declaracion de variables
                status_dato = verificar_dato(array_tokens[0]);

                if (status_dato == true){
                    caso = 1;
                    strcpy(variable, array_tokens[1]);
                    status_variable = verificar_variables(variable);
                    strcpy(variable_valor,array_tokens[3]);

                    if(strcmp(array_tokens[2],operadores[0]) == 0){         
                        status_operador = true;
                    }else{
                        status_operador = false;
                    }

                    status_variable_valor = verificar_variable_valor(variable_valor,array_tokens[0]);
                    

                // Estructura "for"
                }else if (strcmp(array_tokens[0], estructuras[0]) == 0){
                    caso = 2;
                    status_dato = verificar_dato(array_tokens[1]);

                    if (status_dato == true){
                        strcpy(variable,array_tokens[2]);
                        status_variable = verificar_variables(variable);
                    }

                    if (strcmp(array_tokens[3], operadores[0]) == 0){
                        status_operador = true;
                    }else{
                        status_operador = false;
                    }

                    status_num = verificar_num(array_tokens[4]);
                    
                // Estructura "while"
                }else if (strcmp(array_tokens[0], estructuras[1]) == 0){
                    caso = 3;

                    if (strcmp(array_tokens[1],variable) == 0){
                        status_declaracion_variable = true;
                    }else{
                        status_declaracion_variable = false;
                    }

                    status_operador = verificar_operador_comparacion(array_tokens[2]);
                    status_num = verificar_num(array_tokens[3]);
                    
                //Estructura "if"
                }else if(strcmp(array_tokens[0], estructuras[2]) == 0){
                    caso = 4;
                    if (strcmp(array_tokens[1],variable) == 0){
                        status_declaracion_variable = true;
                    }else{
                        status_declaracion_variable = false;
                    }

                    status_operador = verificar_operador_comparacion(array_tokens[2]);
                    status_num = verificar_num(array_tokens[3]);

                // estructura "variable"
                }else if (strcmp(array_tokens[0], variable) == 0){
                    caso = 5;
                    if (j <= 1){
                        status_num = true;
                        status_operador = verificar_operador_doble(array_tokens[1]);
                    }else{
                        status_num = verificar_num(array_tokens[2]);
                    }  

                    if (status_operador == false){
                        status_operador = verificar_operador(array_tokens[1]);
                    }
                    
                    if (status_operador == false){
                        status_operador = verificar_operador_comparacion(array_tokens[1]);
                    }
                }else if (isdigit(*array_tokens[0])){
                    caso = 6;
                    status_num = true; 

                    if (status_operador == false){
                        status_operador = verificar_operador(array_tokens[1]);
                    }
                    
                    if (status_operador == false){
                        status_operador = verificar_operador_comparacion(array_tokens[1]);
                    }

                    if (strcmp(array_tokens[2], variable) == 0){
                        status_declaracion_variable = true;
                    }
                    
                }else{
                    caso = 0;   
                }

                switch (caso)
                {
                case 1: // declaracion de variables
                    if (status_dato == false){
                        printf("ERROR LEXICO (LINEA %i): No se reconoce el tipo de dato o estructura\n",i+1);
                    }
                    if (status_variable == false){
                        printf("ERROR LEXICO (LINEA %i): Caracteres no permitidos en declaracion de variables\n",i+1);
                    }
                    if (status_operador == false){
                        printf("ERROR SINTACTICO (LINEA %i): Operador invalido\n",i+1);
                    }
                    if (status_variable_valor == false){
                        printf("ERROR SEMANTICO (LINEA %i): Valor de la variable no concuerda con el tipo de dato\n",i+1);
                    }
                    if (j > 3){
                       printf("ERROR SINTACTICO (LINEA %i): Se espera menos cantidad de estructuras\n",i+1);
                    }
                    
                    break;
                
                case 2: // for
                    if (status_dato == false){
                        printf("ERROR LEXICO (LINEA %i): No se reconoce el tipo de dato o estructura\n",i+1);
                    }
                    if (status_variable == false){
                        printf("ERROR LEXICO (LINEA %i): Caracteres no permitidos en declaracion de variables\n",i+1);
                    }
                    if (status_operador == false){
                        printf("ERROR SINTACTICO (LINEA %i): Operador invalido\n",i+1);
                    }
                    if (status_num == false){
                        printf("ERROR LEXICO (LINEA %i): Caracter no numerico ingresado\n",i+1);
                    }
                    if (j > 4){
                        printf("ERROR SINTACTICO (LINEA %i): Se espera menos cantidad de estructuras\n",i+1);
                    }
                    break;

                case 3: // while
                    if (status_declaracion_variable == false){
                        printf("ERROR SEMANTICO (LINEA %i): la variable no se declaro con anterioridad\n",i+1);
                    }
                    if (status_operador == false){
                        printf("ERROR SINTACTICO (LINEA %i): Operador invalido\n",i+1);
                    }
                    if (status_num == false){
                        printf("ERROR LEXICO (LINEA %i): Caracter no numerico ingresado\n",i+1);
                    }

                    if (j > 3){
                        printf("ERROR SINTACTICO (LINEA %i): Se espera menos cantidad de estructuras\n",i+1);
                    }
                    
                    break;
                
                case 4: // if
                    if (status_declaracion_variable == false){
                        printf("ERROR SEMANTICO (LINEA %i): la variable no se declaro con anterioridad\n",i+1);
                    }
                    if (status_operador == false){
                        printf("ERROR SINTACTICO (LINEA %i): Operador invalido\n",i+1);
                    }
                    if (status_num == false){
                        printf("ERROR LEXICO (LINEA %i): Caracter no numerico ingresado\n",i+1);
                    }
                    if (j > 3){
                        printf("ERROR SINTACTICO (LINEA %i): Se espera menos cantidad de estructuras\n",i+1);
                    }
                    break;
            
                case 5 : // Variable
                    if (status_num == false){
                        printf("ERROR LEXICO (LINEA %i): Caracter no numerico ingresado\n",i+1);
                    }
                    if (status_operador == false){
                        printf("ERROR SINTACTICO (LINEA %i): Operador invalido\n",i+1);
                    }
                    if (j > 2){
                        printf("ERROR SINTACTICO (LINEA %i): Se espera menos cantidad de estructuras\n",i+1);
                    }
                    break;
                
                case 6 : // num
                    if (status_num == false){
                        printf("ERROR LEXICO (LINEA %i): Caracter no numerico ingresado\n",i+1);
                    }
                    if (status_operador == false){
                        printf("ERROR SINTACTICO (LINEA %i): Operador invalido\n",i+1);
                    }
                    if (status_declaracion_variable == false){
                        printf("ERROR SEMANTICO (LINEA %i): la variable no se declaro con anterioridad\n",i+1);
                    }
                    if (j > 2){
                        printf("ERROR SINTACTICO (LINEA %i): Se espera menos cantidad de estructuras\n",i+1);
                    }
                    break;
                default:
                    printf("ERROR LEXICO (LINEA %i): No se reconoce el tipo de dato o estructura\n",i+1);
                    break;
                }
            }
        }
    }

    
return 0;
}
