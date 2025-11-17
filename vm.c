#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define MAX_VARS 256

typedef struct {
    char name[64];
    int value;
    int initialized;
} Var;

Var vars[MAX_VARS];
int var_count = 0;

Var* find_var(const char* name) {
    for (int i=0;i<var_count;i++) {
        if (strcmp(vars[i].name, name) == 0) return &vars[i];
    }
    return NULL;
}

Var* create_var(const char* name) {
    Var* v = find_var(name);
    if (v) return v;
    if (var_count >= MAX_VARS) return NULL;
    strncpy(vars[var_count].name, name, 63);
    vars[var_count].name[63] = 0;
    vars[var_count].initialized = 0;
    vars[var_count].value = 0;
    var_count++;
    return &vars[var_count-1];
}

void trim(char *s) {
    char *p = s;
    while (*p && (*p==' ' || *p=='\t' || *p=='\r' || *p=='\n')) p++;
    if (p!=s) memmove(s,p,strlen(p)+1);
    size_t len = strlen(s);
    while (len>0 && (s[len-1]=='\n' || s[len-1]=='\r' || s[len-1]==' ' || s[len-1]=='\t')) { s[len-1]=0; len--; }
}

int main(int argc, char** argv) {
    const char* asmfile = "output.asm";
    if (argc >= 2) asmfile = argv[1];

    FILE* f = fopen(asmfile,"r");
    if (!f) {
        perror("Erro ao abrir arquivo de bytecode");
        return 1;
    }

    char line[MAX_LINE];
    printf("VM: interpretando %s\n", asmfile);
    while (fgets(line, sizeof(line), f)) {
        trim(line);
        if (strlen(line)==0) continue;
        
        char instr[64];
        char rest[192];
        instr[0]=0; rest[0]=0;
        int scanned = sscanf(line, "%63s %[^\n]", instr, rest);
        if (scanned < 1) continue;

        if (strcmp(instr,"VAR")==0) {
            trim(rest);
            create_var(rest);
            printf("[VM] declara var '%s'\n", rest);
        } else if (strcmp(instr,"MOV")==0) {
            
            char name[64]; int val;
            if (sscanf(rest, "%63[^,], %d", name, &val) >= 2) {
                trim(name);
                Var* v = create_var(name);
                if (v) { v->value = val; v->initialized = 1; printf("[VM] %s <- %d\n", name, val); }
                else printf("[VM] erro: não criou variável %s\n", name);
            } else {
                printf("[VM] instrução MOV mal formada: %s\n", rest);
            }
        } else if (strcmp(instr,"AQUECER")==0) {
            printf("[VM] AQUECER: aquecendo para %s graus (simulado)\n", rest);
        } else if (strcmp(instr,"DESPEJAR")==0) {
            printf("[VM] DESPEJAR: %s\n", rest);
        } else if (strcmp(instr,"MISTURAR")==0) {
            printf("[VM] MISTURAR por %s\n", rest);
        } else if (strcmp(instr,"ESPERAR")==0) {
            printf("[VM] ESPERAR por %s\n", rest);
        } else if (strcmp(instr,"FAZER_CAFE")==0) {
            printf("[VM] FAZER_CAFE: %s\n", rest);
        } else if (strcmp(instr,"PRINT")==0) {
            printf("[VM] PRINT: %s\n", rest);
        } else if (strcmp(instr,"PAGAR")==0) {
            printf("[VM] PAGAR: %s\n", rest);
        } else if (strcmp(instr, "END_IF") == 0) {
            printf("[VM] END_IF\n");
        } else if (strcmp(instr, "END_WHILE") == 0) {
            printf("[VM] END_WHILE\n");
        } else if (strcmp(instr,"LER_SENSOR")==0) {
            printf("[VM] LER_SENSOR: %s (simulado - valor 1)\n", rest);
         
            char varname[64];
            if (sscanf(rest, "%63s", varname)==1) {
                Var* v = create_var(varname);
                if (v) { v->value = 1; v->initialized = 1; }
            }
        } else if (strcmp(instr,"ALERTA")==0) {
            printf("[VM] ALERTA: %s\n", rest);
        } else {
            printf("[VM] INSTRUÇÃO DESCONHECIDA: %s %s\n", instr, rest);
        }
    }

    fclose(f);
    printf("VM: execução finalizada. Variáveis:\n");
    for (int i=0;i<var_count;i++) {
        printf("  - %s = %d (iniciado? %s)\n", vars[i].name, vars[i].value, vars[i].initialized ? "sim":"nao");
    }
    return 0;
}