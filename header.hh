/*
    lib/read_write_weights/header.hh
    Q@khaa.pk
 */

/*
 * Temporary Inclusion of hyper-parameters.hh
 * 
 * This inclusion serves as an ad-hoc solution to address the current need for 
 * hyper-parameters in this implementation, but this approach may not be 
 * the best long-term solution.
 */
#ifdef READ_TRAINED_SKIP_GRAM_WEIGHTS_TEST_APP_HH
#include "../Skip-gram/lib/WordEmbedding-Algorithms/Word2Vec/Skip-gram/hyper-parameters.hh" 
#elif defined READ_TRAINED_CBOW_WEIGHTS_TEST_APP_HH
#include "../CBOW/lib/WordEmbedding-Algorithms/Word2Vec/CBOW/hyper-parameters.hh" 
#endif

#ifndef READ_WEIGHTS_HEADER_HEADER_HH
#define READ_WEIGHTS_HEADER_HEADER_HH

/*
    w, instance of Collective<E>. The w1 hould have the complete shape
    f, name of the file. An instance of cc_tokenizer::String class 
    t,
 */
#define READ_W_BIN_NEW_ONE(w, f, t)\
{\
    try\
    {\
        w = cc_tokenizer::cooked_read<t>(f, w);\
    }\
    catch(ala_exception& e)\
    {\
        cc_tokenizer::String<char> message = cc_tokenizer::String<char>("READ_W_BIN_NEW_ONE() macro -> ") + cc_tokenizer::String<char>(f) + cc_tokenizer::String<char>(" ") + cc_tokenizer::String<char>(e.what());\
        throw ala_exception(message);\
    }\
}\

/*
    w, instance of Collective<E>. The w1 hould have the complete shape
    f, name of the file. An instance of cc_tokenizer::String class 
    t,
 */
#define READ_W_BIN(w, f, t)\
{\
    try\
    {\
        w = cc_tokenizer::cooked_read<t>(f, w/*.getShape().getN()*/);\
    }\
    catch(ala_exception& e)\
    {\
        cc_tokenizer::String<char> message = cc_tokenizer::String<char>("READ_W_BIN() macro -> ") + cc_tokenizer::String<char>(f) + cc_tokenizer::String<char>(" ") + cc_tokenizer::String<char>(e.what());\
        throw ala_exception(message);\
    }\
}\

/*
    w, instance of Collective<E>. The w1 hould have the complete shape
    f, name of the file. An instance of cc_tokenizer::String class 
    t,
 */
#define WRITE_W_BIN(w, f, t)\
{\
    try\
    {\
        cc_tokenizer::cooked_write<t>(f, w);\
    }\
    catch(ala_exception& e)\
    {\
        cc_tokenizer::String<char> message = cc_tokenizer::String<char>("WRITE_W_BIN() macro -> ") + cc_tokenizer::String<char>(f) + cc_tokenizer::String<char>(" ") + cc_tokenizer::String<char>(e.what());\
        throw ala_exception(message);\
    }\
}\

/*
    @p,  instance of tokenizer
    @w1, instance of Collective<double>
 */
#define  READ_W1(p, w1)\
{\
    p.reset(LINES);\
    p.reset(TOKENS);\
    /* Adjusting line and token counts to account for an off-by-one error in the parser.\
    The parser seems to return one additional line and one extra token than expected,\
    so we subtract 1 from the total counts to ensure we process only the actual lines and tokens */\
    cc_tokenizer::string_character_traits<char>::size_type r = p.get_total_number_of_lines() - 0;\
    p.go_to_next_line();\
    /* Adjusting line and token counts to account for an off-by-one error in the parser.\
    The parser seems to return one additional line and one extra token than expected,\
    so we subtract 1 from the total counts to ensure we process only the actual lines and tokens */\
    cc_tokenizer::string_character_traits<char>::size_type c = p.get_total_number_of_tokens() - 1;\
    p.reset(LINES);\
    try\
    {\
        w1 = Numcy::zeros(DIMENSIONS{c, r, NULL, NULL});\
    }\
    catch (ala_exception& e)\
    {\
        std::cout<< e.what() << std::endl;\
    }\
    cc_tokenizer::string_character_traits<char>::size_type i = 0;\
    while (p.go_to_next_line() != cc_tokenizer::string_character_traits<char>::eof())\
    {\
        cc_tokenizer::string_character_traits<char>::size_type j = 0;\
        p.get_token_by_number(1);\
        while (p.go_to_next_token() != cc_tokenizer::string_character_traits<char>::eof())\
        {\
            w1[i*c + j] = atof(p.get_current_token().c_str());\
            j = j + 1;\
        }\
        i = i + 1; \
    }\
}\

/*
    @p,  instance of tokenizer
    @w1, instance of Collective<double>    
 */
#define READ_W2(p, w2)\
{\
    p.reset(LINES);\
    p.reset(TOKENS);\
    /* Adjusting line and token counts to account for an off-by-one error in the parser.\
    The parser seems to return one additional line and one extra token than expected,\
    so we subtract 1 from the total counts to ensure we process only the actual lines and tokens */\
    cc_tokenizer::string_character_traits<char>::size_type r = p.get_total_number_of_lines() - 0;\
    p.go_to_next_line();\
    /* Adjusting line and token counts to account for an off-by-one error in the parser.\
    The parser seems to return one additional line and one extra token than expected,\
    so we subtract 1 from the total counts to ensure we process only the actual lines and tokens */\
    cc_tokenizer::string_character_traits<char>::size_type c = p.get_total_number_of_tokens() - 1;\
    p.reset(LINES);\
    try\
    {\
        w2 = Numcy::zeros(DIMENSIONS{r, c, NULL, NULL});\
        std::cout<< "r = " << r << ", c = " << c << std::endl;\
    }\
    catch (ala_exception& e)\
    {\
        std::cout<< e.what() << std::endl;\
    }\
    cc_tokenizer::string_character_traits<char>::size_type i = 0;\
    while (p.go_to_next_line() != cc_tokenizer::string_character_traits<char>::eof())\
    {\
        cc_tokenizer::string_character_traits<char>::size_type j = 0;\
        p.get_token_by_number(1);\
        while (p.go_to_next_token() != cc_tokenizer::string_character_traits<char>::eof())\
        {\
            w2[j*c + i] = atof(p.get_current_token().c_str());\
            j = j + 1;\
        }\
        i = i + 1; \
    }\
}\

#define READ_W2_ChatGPT_With_W1(p, w1, w2)\
{\
    p.reset(LINES);\
    p.reset(TOKENS);\
    /* Get the total line and token counts, with adjustments */\
    cc_tokenizer::string_character_traits<char>::size_type r = p.get_total_number_of_lines() - 0;\
    p.go_to_next_line();\
    cc_tokenizer::string_character_traits<char>::size_type c = p.get_total_number_of_tokens() - 1;\
    p.reset(LINES);\
    if (w1.getShape().getDimensionsOfArray().getNumberOfInnerArrays() != r || w1.getShape().getNumberOfColumns() != c)\
    {\
        r = w1.getShape().getDimensionsOfArray().getNumberOfInnerArrays();\
        c = w1.getShape().getNumberOfColumns();\
    }\
    try\
    {\
        w2 = Numcy::zeros(DIMENSIONS{r, c, NULL, NULL});\
        std::cout << "Initialized W2 with dimensions: " << r << " X " << c << std::endl;\
    }\
    catch (ala_exception& e)\
    {\
        std::cout << "Exception while initializing W2: " << e.what() << std::endl;\
    }\
    cc_tokenizer::string_character_traits<char>::size_type i = 0;\
    /* Iterate over lines, with an explicit EOF check */\
    while (p.go_to_next_line() != cc_tokenizer::string_character_traits<char>::eof())\
    {\
        cc_tokenizer::string_character_traits<char>::size_type j = 0;\
        p.get_token_by_number(1);\
        /* Check if we have reached the last line, in case of unexpected empty line at EOF */\
        if (i >= r) {\
            std::cout << "Warning: Attempted to read past the last expected line. Breaking early." << std::endl;\
            break;\
        }\
        /* Process tokens within the line */\
        while (p.go_to_next_token() != cc_tokenizer::string_character_traits<char>::eof())\
        {\
            if (j >= c) {\
                std::cout << "Warning: Attempted to read past the last expected token in line " << i << ". Breaking token loop." << std::endl;\
                break;\
            }\
            w2[j * c + i] = atof(p.get_current_token().c_str());\
            j = j + 1;\
        }\
        i = i + 1;\
    }\
    std::cout << "Final line read count: " << i << std::endl;\
    std::cout << "Expected line count: " << r << std::endl;\
}\

#define READ_W2_ChatGPT(p, w2)\
{\
    p.reset(LINES);\
    p.reset(TOKENS);\
    /* Get the total line and token counts, with adjustments */\
    cc_tokenizer::string_character_traits<char>::size_type r = p.get_total_number_of_lines() - 0;\
    p.go_to_next_line();\
    cc_tokenizer::string_character_traits<char>::size_type c = p.get_total_number_of_tokens() - 1;\
    p.reset(LINES);\
    try\
    {\
        w2 = Numcy::zeros(DIMENSIONS{r, c, NULL, NULL});\
        std::cout << "Initialized W2 with dimensions: " << r << " X " << c << std::endl;\
    }\
    catch (ala_exception& e)\
    {\
        std::cout << "Exception while initializing W2: " << e.what() << std::endl;\
    }\
    cc_tokenizer::string_character_traits<char>::size_type i = 0;\
    /* Iterate over lines, with an explicit EOF check */\
    while (p.go_to_next_line() != cc_tokenizer::string_character_traits<char>::eof())\
    {\
        cc_tokenizer::string_character_traits<char>::size_type j = 0;\
        p.get_token_by_number(1);\
        /* Check if we have reached the last line, in case of unexpected empty line at EOF */\
        if (i >= r) {\
            std::cout << "Warning: Attempted to read past the last expected line. Breaking early." << std::endl;\
            break;\
        }\
        /* Process tokens within the line */\
        while (p.go_to_next_token() != cc_tokenizer::string_character_traits<char>::eof())\
        {\
            if (j >= c) {\
                std::cout << "Warning: Attempted to read past the last expected token in line " << i << ". Breaking token loop." << std::endl;\
                break;\
            }\
            w2[j * c + i] = atof(p.get_current_token().c_str());\
            j = j + 1;\
        }\
        i = i + 1;\
    }\
    std::cout << "Final line read count: " << i << std::endl;\
    std::cout << "Expected line count: " << r << std::endl;\
}\

/*    
    @w2, instance of Collective<double>, these weights are written to @f
    @f,  name of file where @w2 are written to, instance of class String
    @v,  vocabulary, instance of class corpus    
 */
#define WRITE_W2_TO_TEXT_FILE(W2, f, v)\
{\
    for (cc_tokenizer::string_character_traits<char>::size_type i = 0; i < W2.getShape().getNumberOfColumns(); i++)\
    {\
        cc_tokenizer::String<char> line;\
        line = v[i + INDEX_ORIGINATES_AT_VALUE] + cc_tokenizer::String<char>(": ");\
        cc_tokenizer::string_character_traits<char>::size_type j = 0;\
        for (; j < W2.getShape().getNumberOfRows();)\
        {\
            cc_tokenizer::String<char> num(W2[j*W2.getShape().getNumberOfColumns() + i]);\
            j = j + 1;\
            if (j < W2.getShape().getNumberOfRows())\
            {\
                line = line + num + cc_tokenizer::String<char>(" ");\
            }\
            else\
            {\
                line = line + num;\
            }\
        }\
        line = line + cc_tokenizer::String<char>("\n");\
        cc_tokenizer::cooked_write(f, line);\
    }\
}\

/*    
    @w1, instance of Collective<double>, these weights are written to @f
    @f,  name of file where @w1 are written to, instance of class String
    @v,  vocabulary, instance of class corpus    
 */
#define WRITE_W1_TO_TEXT_FILE(W1, f, v)\
{\
    for (cc_tokenizer::string_character_traits<char>::size_type i = 0; i < W1.getShape().getNumberOfRows() /*- 1*/; i++)\
    {\
        cc_tokenizer::String<char> line = v[i + INDEX_ORIGINATES_AT_VALUE] + cc_tokenizer::String<char>(" ");\
            cc_tokenizer::string_character_traits<char>::size_type j = 0;\
            for (; j < W1.getShape().getNumberOfColumns();)\
            {\
                cc_tokenizer::String<char> num(W1[i*W1.getShape().getNumberOfColumns() + j]);\
                j = j + 1;\
                if (j < W1.getShape().getNumberOfColumns())\
                {\
                   line = line + num + cc_tokenizer::String<char>(" ");\
                }\
                else\
                {\
                    line = line + num;\
                }\
            }\
            line = line + cc_tokenizer::String<char>("\n");\
            cc_tokenizer::cooked_write(cc_tokenizer::String<char>(f), line);\
    }\
}\

/*    
    @w1, instance of Collective<double>, these weights are written to @f
    @f,  name of file where @w1 are written to, instance of class String
    @v,  vocabulary, instance of class corpus
 */
#define WRITE_W1(w1, f, v)\
{\
for (cc_tokenizer::string_character_traits<char>::size_type i = 0; i < v.numberOfUniqueTokens(); i++)\
    {\
        cc_tokenizer::String<char> line;\
        line = line + v[i + INDEX_ORIGINATES_AT_VALUE] + cc_tokenizer::String<char>(" ");\
        cc_tokenizer::string_character_traits<char>::size_type j = 0;\
        for (; j < SKIP_GRAM_EMBEDDNG_VECTOR_SIZE;)\
        {\
            cc_tokenizer::String<char> num(w1[i*SKIP_GRAM_EMBEDDNG_VECTOR_SIZE + j]);\
            j++;\
            if (j < SKIP_GRAM_EMBEDDNG_VECTOR_SIZE)\
            {\
                line = line + num + cc_tokenizer::String<char>(" ");\
            }\
            else\
            {\
                line = line + num;\
            }\
        }\
        line = line + cc_tokenizer::String<char>("\n");\
        cc_tokenizer::cooked_write(f, line);\
    }\
}\

/*    
    @w2, instance of Collective<double>, these weights are written to @f
    @f,  name of file where @w1 are written to, instance of class String
    @v,  vocabulary, instance of class corpus
 */
#define WRITE_W2(w2, f, v)\
{\
    for (cc_tokenizer::string_character_traits<char>::size_type i = 0; i < v.numberOfUniqueTokens(); i++)\
    {\
        cc_tokenizer::String<char> line;\
        line = line + v[i + INDEX_ORIGINATES_AT_VALUE] + cc_tokenizer::String<char>(" ");\
        cc_tokenizer::string_character_traits<char>::size_type j = 0;\
        for (; j < SKIP_GRAM_EMBEDDNG_VECTOR_SIZE;)\
        {\
            cc_tokenizer::String<char> num(w2[j*SKIP_GRAM_EMBEDDNG_VECTOR_SIZE + i]);\
            j++;\
            if (j < SKIP_GRAM_EMBEDDNG_VECTOR_SIZE)\
            {\
                line = line + num + cc_tokenizer::String<char>(" ");\
            }\
            else\
            {\
                line = line + num + cc_tokenizer::String<char>("\n");\
            }\
        }\
        /*line = line + cc_tokenizer::String<char>("\n");*/\
        cc_tokenizer::cooked_write(f, line);\
    }\
}\

#endif