#include "test_cases.h"
#include "grading.h"
#include <stdlib.h>
#include <string.h>

#define HTML_OPEN_TAG    "<html>\n"
#define HTML_CLOSE_TAG   "</html>"
#define HEAD_OPEN_TAG    "\t<head>\n"
#define HEAD_CLOSE_TAG   "\t</head>\n"
#define BODY_OPEN_TAG    "\t<body>\n"
#define BODY_CLOSE_TAG   "\t</body>\n"
#define TITLE_OPEN_TAG   "\t\t<title>"
#define TITLE_CLOSE_TAG  "</title>\n"
#define TABLE_OPEN_TAG   "\t\t<table style=\"width: 40%\">\n"
#define TABLE_CLOSE_TAG  "\t\t</table>\n"
#define TR_OPEN_TAG      "\t\t\t<tr>\n"
#define TR_CLOSE_TAG     "\t\t\t</tr>\n"
#define TH_OPEN_TAG      "\t\t\t\t<th style=\"text-align: center\">"
#define TH_CLOSE_TAG     "</th>\n"
#define TD_OPEN_TAG      "\t\t\t\t<td style=\"text-align: center\">"
#define TD_CLOSE_TAG     "</td>\n"
#define H1_OPEN_TAG      "\t\t<h1>"
#define H1_CLOSE_TAG     "</h1>\n"

#define COLUMN_1         "Test data"
#define COLUMN_2         "Expected result"
#define COLUMN_3         "Actual result"
#define COLUMN_4         "Pass/Fail"

#define BUFF_SIZE 19
#define TEST_RESOLUTION(result, expected) ((result == expected) ? "Pass" : "Fail")

static FILE *create_HTML_file(const char *restrict filename);
static void close_HTML_file(FILE *file);
static void set_HTML_head(FILE *file, const char *restrict title);
static void set_HTML_body(FILE *file, const float *restrict data, const char **restrict expected, const char **restrict results, size_t length);

void execute_test_cases()
{
    FILE *file;
    const float test_data[BUFF_SIZE] = 
    {
        -3.50f, 30.0f, 55.55f, 70.0f, 78.5f, 86.0f, 150.7f, -1.0f, 0.0f, 49.99f,
        50.0f, 62.99f, 63.0f, 72.99f, 73.0f, 82.99f, 83.0f, 100.0f, 101.0f
    };
    const char *expected_results[BUFF_SIZE] = 
    { 
        NULL, GRADE_FAIL, GRADE_PASS, GRADE_CREDIT, GRADE_DISTINCTION, GRADE_HIGH_DISTINCTION, NULL, NULL, GRADE_FAIL,
        GRADE_FAIL, GRADE_PASS, GRADE_PASS, GRADE_CREDIT, GRADE_CREDIT, GRADE_DISTINCTION, GRADE_DISTINCTION,
        GRADE_HIGH_DISTINCTION, GRADE_HIGH_DISTINCTION, NULL
    };
    const char *final_results[BUFF_SIZE];

    for (int i = 0; i < BUFF_SIZE; i++)
        final_results[i] = get_grade(test_data[i]);
    
    file = create_HTML_file("test-cases-table.html");
    set_HTML_head(file, "Test cases");
    set_HTML_body(file, test_data, expected_results, final_results, BUFF_SIZE);
    close_HTML_file(file);
}

static FILE *create_HTML_file(const char *restrict filename)
{
    FILE *file = fopen(filename, "w+");

    if (file)
        fputs(HTML_OPEN_TAG, file);

    return file;
}

static void close_HTML_file(FILE *file)
{
    if (file)
    {
        fputs(HTML_CLOSE_TAG, file);
        fclose(file);
    }
}

static void set_HTML_head(FILE *file, const char *restrict title)
{
    if (file && title)
        fprintf(file, "%s%s%s%s%s", HEAD_OPEN_TAG, TITLE_OPEN_TAG, title, TITLE_CLOSE_TAG, HEAD_CLOSE_TAG);
}

static void set_HTML_body(FILE *file, const float *restrict data, const char **restrict expected, const char **restrict results, size_t length)
{
    if (file && data && expected && results)
    {
        fputs(BODY_OPEN_TAG, file);
        fprintf(file, "%s%s%s", H1_OPEN_TAG, "Test cases", H1_CLOSE_TAG);
        fputs(TABLE_OPEN_TAG, file);
        fputs(TR_OPEN_TAG, file);
        fprintf(file, "%s%s%s", TH_OPEN_TAG, COLUMN_1, TH_CLOSE_TAG);
        fprintf(file, "%s%s%s", TH_OPEN_TAG, COLUMN_2, TH_CLOSE_TAG);
        fprintf(file, "%s%s%s", TH_OPEN_TAG, COLUMN_3, TH_CLOSE_TAG);
        fprintf(file, "%s%s%s", TH_OPEN_TAG, COLUMN_4, TH_CLOSE_TAG);
        fputs(TR_CLOSE_TAG, file);

        for (int i = 0; i < length; i++)
        {
            fputs(TR_OPEN_TAG, file);
            fprintf(file, "%s%.2f%s", TD_OPEN_TAG, data[i] , TD_CLOSE_TAG);
            fprintf(file, "%s%s%s", TD_OPEN_TAG, expected[i], TD_CLOSE_TAG);
            fprintf(file, "%s%s%s", TD_OPEN_TAG, results[i], TD_CLOSE_TAG);
            fprintf(file, "%s%s%s", TD_OPEN_TAG, TEST_RESOLUTION(results[i], expected[i]), TD_CLOSE_TAG);
            fputs(TR_CLOSE_TAG, file);
        }

        fputs(TABLE_CLOSE_TAG, file);
        fputs(BODY_CLOSE_TAG, file);
    }
}