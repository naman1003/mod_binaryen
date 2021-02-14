/*
 * Copyright 2016 WebAssembly Community Group participants
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//
// wasm2asm console tool
//

#include "support/colors.h"
#include "support/file.h"
#include "wasm-io.h"

#include "tool-options.h"

using namespace cashew;
using namespace wasm;







#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1000

/* Function declaration */
void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);


    /*
     * Repeat till all occurrences are replaced. 
     */
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        // Bakup current line
        strcpy(temp, str);

        // Index of current found word
        index = pos - str;

        // Terminate str after word found index
        str[index] = '\0';

        // Concatenate str with new word 
        strcat(str, newWord);
        
        // Concatenate str with remaining words after 
        // oldword found index.
        strcat(str, temp + index + owlen);
    }
}





int main(int argc, const char* argv[]) {






  std::string sourceMapFilename;
  ToolOptions options("wasm-dis",
                      "Un-assemble a .wasm (WebAssembly binary format) into a "
                      ".wat (WebAssembly text format)");
  options
    .add("--output",
         "-o",
         "Output file (stdout if not specified)",
         Options::Arguments::One,
         [](Options* o, const std::string& argument) {
           o->extra["output"] = argument;
           Colors::setEnabled(false);
         })
    .add(
      "--source-map",
      "-sm",
      "Consume source map from the specified file to add location information",
      Options::Arguments::One,
      [&sourceMapFilename](Options* o, const std::string& argument) {
        sourceMapFilename = argument;
      })
    .add_positional("INFILE",
                    Options::Arguments::One,
                    [](Options* o, const std::string& argument) {
                      o->extra["infile"] = argument;
                    });
  options.parse(argc, argv);



if( access( options.extra["infile"].c_str(), F_OK ) == 0 )
{
  
FILE * fPtr;
    FILE * fTemp;
    //char path[100];
    
    char buffer[BUFFER_SIZE];
    //char oldWord[100], newWord[100];


    //printf("Enter path of source file: ");
    //scanf("%s", path);
    //path = options.extra["infile"].c_str();

    //printf("Enter word to replace: ");
    //scanf("%s", oldWord);
    char oldWord[] = "i32xy";
    //char oldWord1[] = "i64yz";

    //printf("Replace '%s' with: ");
    //scanf("%s", newWord);
    char newWord[] = "i32";
    //char newWord1[] = "i64";



    /*  Open all required files */
    fPtr  = fopen(options.extra["infile"].c_str(), "r");
    fTemp = fopen("replace.tmp", "w"); 

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }


    /*
     * Read line from source file and write to destination 
     * file after replacing given word.
     */
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        // Replace all occurrence of word from current line
        replaceAll(buffer, oldWord, newWord);

        // After replacing write it to temp file.
        fputs(buffer, fTemp);
    }

   


    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);


    /* Delete original source file */
    remove(options.extra["infile"].c_str());

    /* Rename temp file as original file */
    rename("replace.tmp", options.extra["infile"].c_str());

    //printf("\nSuccessfully replaced all occurrences of '%s' with '%s'.", oldWord, newWord);






 
    char oldWord1[] = "i64yz";

    //printf("Replace '%s' with: ");
    //scanf("%s", newWord);
    
    char newWord1[] = "i64";



    /*  Open all required files */
    fPtr  = fopen(options.extra["infile"].c_str(), "r");
    fTemp = fopen("replace.tmp", "w"); 

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }


    /*
     * Read line from source file and write to destination 
     * file after replacing given word.
     */
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        // Replace all occurrence of word from current line
        replaceAll(buffer, oldWord1, newWord1);

        // After replacing write it to temp file.
        fputs(buffer, fTemp);
    }

   


    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);


    /* Delete original source file */
    remove(options.extra["infile"].c_str());

    /* Rename temp file as original file */
    rename("replace.tmp", options.extra["infile"].c_str());

}







  if (options.debug) {
    std::cerr << "parsing binary..." << std::endl;
  }
  Module wasm;
  try {
    ModuleReader().readBinary(options.extra["infile"], wasm, sourceMapFilename);
  } catch (ParseException& p) {
    p.dump(std::cerr);
    std::cerr << '\n';
    Fatal() << "error in parsing wasm binary";
  } catch (MapParseException& p) {
    p.dump(std::cerr);
    std::cerr << '\n';
    Fatal() << "error in parsing wasm source mapping";
  }

  options.applyFeatures(wasm);

  // TODO: Validation. However, validating would mean that users are forced to
  //       run with  wasm-dis -all  or such, to enable the features (unless the
  //       features section is present, but that's rare in general). It would be
  //       better to have an "autodetect" code path that enables used features
  //       eventually.

  if (options.debug) {
    std::cerr << "Printing..." << std::endl;
  }
  Output output(options.extra["output"], Flags::Text);
  output.getStream() << wasm << '\n';

  if (options.debug) {
    std::cerr << "Done." << std::endl;
  }
}
