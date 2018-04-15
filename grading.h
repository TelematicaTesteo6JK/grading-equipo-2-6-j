#ifndef GRADING_H
#define GRADING_H

#define GRADE_FAIL              "N"
#define GRADE_PASS              "P"
#define GRADE_CREDIT            "C"
#define GRADE_DISTINCTION       "D"
#define GRADE_HIGH_DISTINCTION  "HD"

#ifdef __cplusplus
extern "C" {
#endif

const char *get_grade(float scale);

#ifdef __cplusplus
}
#endif

#endif