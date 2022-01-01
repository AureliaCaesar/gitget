#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* GetRepoName(char* repo)
{
    int len = strlen(repo);

    char* buildingString = malloc(len);
    memset(buildingString, 0, len);
    int slashCount = 0;
    int startIndex = 0;
    int writtenIndices = 0;
    
    for (int i = 0; i < len; i++)
    {
        if (slashCount == 4)
        {
            if (repo[i] == '.')
            {
                buildingString[i - startIndex] = '\0';
                break;
            }

            buildingString[i - startIndex] = repo[i];
            writtenIndices++;
        }

        if (repo[i] == '/')
        {
            slashCount += 1;
            startIndex = i + 1;
        }
    }

    char* finalString = malloc(writtenIndices);
    memcpy(finalString, buildingString, writtenIndices);
    free(buildingString);

    return finalString;
}

char* ConcatenateStrings(char* one, char* two)
{
    int len = strlen(one) + strlen(two) + 1;
    char* result = malloc(strlen(one) + strlen(two) + 1);
    memset(result, 0, len);

    int idx = 0;

    for (int i = 0; i < strlen(one); i++)
    {
        result[i] = one[i];
        idx++;
    }

    for (int i = 0; i < strlen(two); i++)
    {
        result[idx] = two[i];
        idx++;
    }

    return result;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        puts("Usage: gitget <source url>");
        return -1;
    }

    char* fetchingStringBase = "Fetching from ";
    char* fetchingString = ConcatenateStrings(fetchingStringBase, argv[1]);
    puts(fetchingString);
    free(fetchingString);

    char* cloneBase = "git clone ";
    char* cloneString = ConcatenateStrings(cloneBase, argv[1]);
    if (system(cloneString) != 0)
    {
        puts("Git clone failed.");
        return -2;
    }
    free(cloneString);

    char* actualRepoName = GetRepoName(argv[1]);

    if (chdir(actualRepoName) != 0)
    {
        puts("Directory change failed.");
        return -3;
    }
    free(actualRepoName);

    puts("Building...");
    if (system("sudo make") != 0)
    {
        puts("Build failed.");
        return -4;
    }

    puts("Installing...");
    if (system("sudo make install") != 0)
    {
        puts("Install failed.");
        return -5;
    }

    puts("Done.");
    return 0;
}
