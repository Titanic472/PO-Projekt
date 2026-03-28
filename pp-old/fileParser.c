#include "fileParser.h"

FILE* openFile(char* fileName, char* mode){
    FILE* file = fopen(fileName, mode);
    if (file != NULL) {
        return file;
    }
    else{
        fprintf(stderr, "CAN'T OPEN FILE: %s", fileName);
        usleep(10000000);
        return NULL;
    }
} 

bool checkFileExists(char* fileName){
    FILE* file = fopen(fileName, "r");
    if (file != NULL) {
        fclose(file);
        return true;
    }
    else {
        return false;
    }
}

fileEntry splitLine(char* line){
    fileEntry entry;

    entry.key = strsep(&line, ":");
    if( entry.key[0] == '}'){
       entry.isHeader = CATEGORY_END_HEADER;
       return entry;
    }
    entry.type = (char)(strsep(&line, ":")[0]);
    if(entry.type == '{'){
        entry.isHeader = CATEGORY_START_HEADER;
        entry.value = NULL;
    }
    else{
        entry.isHeader = CATEGORY_NO_HEADER;
        entry.value = strsep(&line, ";");
    }
    return entry;
}

void loadField(void* field, fileEntry line){
    switch (line.type){
        case 'i':
            *((int*)field) = atoi(line.value);
            break;
        case 'f':
            *((float*)field) = atof(line.value);
            break;
        case 's':
            //strip from " if present
            if(line.value[0] == '\"' && line.value[strlen(line.value)-1] == '\"'){
                line.value[strlen(line.value)-1] = '\0';
                line.value++;
            }

            size_t len = strlen(line.value) + 1;
            char *str = (char*)malloc(len);
            if(str == NULL) {
                fprintf(stderr, "MEMORY ALLOCATION FAILED\n");
                usleep(10000000);
                break;
            }
            strcpy(str, line.value);
            *((char**)field) = str;  // Store pointer to allocated string
            break;
        default:
            fprintf(stderr, "UNKNOWN TYPE: %c", line.type);
            usleep(10000000);
            break;
    }
}

bool getCategory(FILE* file, char* category){
    char line[LINE_MAX_SIZE];
    fileEntry currLine;

    while (fgets(line, sizeof(line), file)) {
        currLine = splitLine(line);
        if(currLine.isHeader == CATEGORY_START_HEADER && strcmp(currLine.key, category) == 0){
            return true;
        }
    }
    return false;
}

bool getEntry(FILE* file, char* key, void* field){
    char line[LINE_MAX_SIZE];
    fileEntry currLine;

    while (fgets(line, sizeof(line), file)) {
        currLine = splitLine(line);
        if(currLine.isHeader == CATEGORY_END_HEADER){
            return false;
        }
        else if(strcmp(currLine.key, key) == 0){
            loadField(field, currLine);
            return true;
        }
    }
    return false;
}

void loadEntry(void* field, char* fileName, char* key, char* category, char* subcategory){
    FILE* file = openFile(fileName, "r");
    if(file==NULL)return;

    if(getCategory(file, category)){
        if(strcmp(subcategory, "") == 0){
            if(!getEntry(file, key, field)){
                fprintf(stderr, "END OF CATEGORY REACHED WITHOUT FINDING KEY: %s\n", key);
                usleep(10000000);
            }
        }
        else{
            if(getCategory(file, subcategory)){
                if(!getEntry(file, key, field)){
                    fprintf(stderr, "END OF CATEGORY REACHED WITHOUT FINDING KEY: %s\n", key);
                    usleep(10000000);
                }
            }
            else{
                fprintf(stderr, "END OF CATEGORY REACHED WITHOUT FINDING SUBCATEGORY: %s\n", subcategory);
                usleep(10000000);
            }
        }
    }
    fclose(file);
}

void exportRankData(int rank[RANKINGS_PLAYER_AMOUNT], char players[RANKINGS_PLAYER_AMOUNT][32]){
    FILE* file = openFile(RANKINGS_FILENAME, "w");
    char buf[LINE_MAX_SIZE];
    snprintf(buf, sizeof(buf), "%s:{\n", RANKINGS_SCORES_CATEGORY);
    fputs(buf, file);
    for(int i = 0; i<RANKINGS_PLAYER_AMOUNT; ++i){
        snprintf(buf, sizeof(buf), "%d:i:%d;\n", i, rank[i]);
        fputs(buf, file);
    }
    fputs("}\n", file);
    snprintf(buf, sizeof(buf), "%s:{\n", RANKINGS_PLAYERS_CATEGORY);
    fputs(buf, file);
    for(int i = 0; i<RANKINGS_PLAYER_AMOUNT; ++i){
        snprintf(buf, sizeof(buf), "%d:s:\"%s\";\n", i, players[i]);
        fputs(buf, file);
    }
    fputs("}", file);
    fclose(file);
}