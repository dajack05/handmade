#pragma once

unsigned int StrLen(const char *str);
void StrCopy(const char *from, char *to, unsigned int maxLength);
bool StrEqual(const char *a, const char *b);
int StrToInt(const char *input);

const char *StrAppend(const char *a, const char *b);

const char *StrFromInt(const int value);
const char *StrFromDouble(const double &value);
