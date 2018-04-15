#include "grading.h"
#include <stdio.h>

const char *get_grade(float scale)
{
    if (scale < 0.0f || scale > 100.0f)
        return NULL;
    else if (scale >= 0.0f && scale <= 49.99f)
        return GRADE_FAIL;
    else if (scale >= 50.0f && scale <= 62.99f)
        return GRADE_PASS;
    else if (scale >= 63.0f && scale <= 72.99f)
        return GRADE_CREDIT;
    else if (scale >= 73.0f && scale <= 82.99f)
        return GRADE_DISTINCTION;
    else
        return GRADE_HIGH_DISTINCTION;
}