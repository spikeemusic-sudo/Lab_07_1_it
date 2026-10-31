#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_07_1_it/Lab_07_1_it.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest71it
{
	TEST_CLASS(UnitTest71it)
	{
	public:

		TEST_METHOD(TestCalcFunction)
		{
			// Arrange: підготовка даних
			int rowCount = 2;
			int colCount = 2;
			int** a = new int* [rowCount];

			// Елемент a[0][0]=11 (непарне, сума індексів 0+0=0, 0%7==0) -> виняток, не рахуємо, не обнуляємо
			// Елемент a[0][1]=10 (парне) -> рахуємо, обнуляємо
			a[0] = new int[colCount] { 11, 10 };

			// Елемент a[1][0]=13 (непарне, сума індексів 1+0=1, 1%7!=0) -> рахуємо, обнуляємо
			// Елемент a[1][1]=14 (парне) -> рахуємо, обнуляємо
			a[1] = new int[colCount] { 13, 14 };

			int S = 0;
			int k = 0;

			int expected_S = 10 + 13 + 14; // 37
			int expected_k = 3;

			// Act: виконання функції
			Calc(a, rowCount, colCount, S, k);

			// Assert: перевірка результатів
			Assert::AreEqual(expected_S, S);
			Assert::AreEqual(expected_k, k);

			// Перевірка заміни потрібних елементів на 0
			Assert::AreEqual(11, a[0][0]); // Залишився без змін
			Assert::AreEqual(0, a[0][1]);  // Замінено на 0
			Assert::AreEqual(0, a[1][0]);  // Замінено на 0
			Assert::AreEqual(0, a[1][1]);  // Замінено на 0

			// Очищення пам'яті
			delete[] a[0];
			delete[] a[1];
			delete[] a;
		}
	};
}