#pragma once

#include <Windows.h>
#include <stdio.h>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include <random>
#include <Psapi.h>
#include <atomic>
#include <chrono>
#include <thread>
#include <assert.h>
#include <string>
#include <fstream>
#include <iomanip>

#pragma warning(disable : 4244)
#pragma warning(disable : 4227)
#pragma warning(disable : 4172)
#pragma warning(disable : 4307)
#pragma warning(disable : 4996)

typedef void EXECUTE;
typedef PVOID PEXECUTE;

#undef GetProp