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
#include "wasm-s-parser.h"
#include "wasm-validator.h"

#include "tool-options.h"
#include "tool-utils.h"

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








  bool debugInfo = false;
  std::string symbolMap;
  std::string sourceMapFilename;
  std::string sourceMapUrl;
  ToolOptions options("wasm-as",
                      "Assemble a .wat (WebAssembly text format) into a .wasm "
                      "(WebAssembly binary format)");
  options.extra["validate"] = "wasm";
  options
    .add("--output",
         "-o",
         "Output file (stdout if not specified)",
         Options::Arguments::One,
         [](Options* o, const std::string& argument) {
           o->extra["output"] = argument;
           Colors::setEnabled(false);
         })
    .add("--validate",
         "-v",
         "Control validation of the output module",
         Options::Arguments::One,
         [](Options* o, const std::string& argument) {
           if (argument != "web" && argument != "none" && argument != "wasm") {
             Fatal() << "Valid arguments for --validate flag are 'wasm', "
                        "'web', and 'none'.\n";
           }
           o->extra["validate"] = argument;
         })
    .add("--debuginfo",
         "-g",
         "Emit names section and debug info",
         Options::Arguments::Zero,
         [&](Options* o, const std::string& arguments) { debugInfo = true; })
    .add("--source-map",
         "-sm",
         "Emit source map to the specified file",
         Options::Arguments::One,
         [&sourceMapFilename](Options* o, const std::string& argument) {
           sourceMapFilename = argument;
         })
    .add("--source-map-url",
         "-su",
         "Use specified string as source map URL",
         Options::Arguments::One,
         [&sourceMapUrl](Options* o, const std::string& argument) {
           sourceMapUrl = argument;
         })
    .add("--symbolmap",
         "-s",
         "Emit a symbol map (indexes => names)",
         Options::Arguments::One,
         [&](Options* o, const std::string& argument) { symbolMap = argument; })
    .add_positional("INFILE",
                    Options::Arguments::One,
                    [](Options* o, const std::string& argument) {
                      o->extra["infile"] = argument;
                    });
  options.parse(argc, argv);
  
   //printf("Usage: %s number-of-rings\n",extra["infile"].c_str());

 
  // default output is infile with changed suffix
  if (options.extra.find("output") == options.extra.end()) {
    options.extra["output"] =
      removeSpecificSuffix(options.extra["infile"], ".wat") + ".wasm";
  }
  //printf("Usage: %s number-of-rings\n",options.extra["infile"].c_str());



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



  auto input(read_file<std::string>(options.extra["infile"], Flags::Text));

  Module wasm;

  //printf("Usage: %s number-of-rings\n",input.c_str());

  try {
    if (options.debug) {
      std::cerr << "s-parsing..." << std::endl;
    }
    SExpressionParser parser(const_cast<char*>(input.c_str()));
    Element& root = *parser.root;
    if (options.debug) {
      std::cerr << "w-parsing..." << std::endl;
    }
    SExpressionWasmBuilder builder(wasm, *root[0], options.profile);
  } catch (ParseException& p) {
    p.dump(std::cerr);
    Fatal() << "error in parsing input";
  }

  options.applyFeatures(wasm);

  if (options.extra["validate"] != "none") {
    if (options.debug) {
      std::cerr << "Validating..." << std::endl;
    }
    if (!wasm::WasmValidator().validate(
          wasm,
          WasmValidator::Globally |
            (options.extra["validate"] == "web" ? WasmValidator::Web : 0))) {
      Fatal() << "Error: input module is not valid.\n";
    }
  }

  if (options.debug) {
    std::cerr << "writing..." << std::endl;
  }
  ModuleWriter writer;
  writer.setBinary(true);
  writer.setDebugInfo(debugInfo);
  if (sourceMapFilename.size()) {
    writer.setSourceMapFilename(sourceMapFilename);
    writer.setSourceMapUrl(sourceMapUrl);
  }
  if (symbolMap.size() > 0) {
    writer.setSymbolMap(symbolMap);
  }
  writer.write(wasm, options.extra["output"]);

  if (options.debug) {
    std::cerr << "Done." << std::endl;
  }
}
