#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1(10);
	for (int i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	TDynamicVector<int> v2(v1);
	EXPECT_EQ(v1.size(), v2.size());
	for (int i = 0; i<10; i++) {
		EXPECT_EQ(v1[i], v2[i]);
	}
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(10);
	v1[0] = 52;
	TDynamicVector<int> v2(10);
	v2 = v1;
	v2[0] = 68;
	EXPECT_NE(v1[0], v2[0]);
 
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v.at(v.size() + 1));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(10);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(10), v2(10);
	ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	const int size1 = 3, size2 = 4;
	TDynamicVector<int> v1(size1), v2(size2);
	for (int i = 0; i < size1; i++)
	{
		v1[i] = i;
	}
	v2 = v1;

	EXPECT_EQ(v2.size(), size1);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(9), v2(4);

	ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(7);
	for (int i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	TDynamicVector<int> v2(v1);
	EXPECT_EQ(v1 == v2, true);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v1(7);
	for (int i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	EXPECT_EQ(v1 == v1, true);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(4), v2(5);
	EXPECT_EQ(v1 == v2, false);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v1(5), v2(5);
	for (int i = 0; i < 5; i++) {
		v1[i] = 2;
	}
	for (int i = 0; i < 5; i++) {
		v2[i] = 4;
	}
	for (int i = 0; i < 5; i++) {
		v1[i] = v1[i] + 2;
	}
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v1(5), v2(5);
	for (int i = 0; i < 5; i++) {
		v1[i] = 4;
	}
	for (int i = 0; i < 5; i++) {
		v2[i] = 2;
	}
	for (int i = 0; i < 5; i++) {
		v1[i] = v1[i] - 2;
	}
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v1(5), v2(5);
	for (int i = 0; i < 5; i++) {
		v1[i] = 2;
	}
	for (int i = 0; i < 5; i++) {
		v2[i] = 4;
	}
	for (int i = 0; i < 5; i++) {
		v1[i] = v1[i] * 2;
	}
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5), v2(5), v3(5);
	for (int i = 0; i < 5; i++)
	{
		v1[i] = 1;
	}
	for (int i = 0; i < 5; i++)
	{
		v2[i] = 2;
	}
	for (int i = 0; i < 5; i++)
	{
		v3[i] = 3;
	}
	EXPECT_EQ(v1 + v2, v3);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(7), v2(5);
	for (int i = 0; i < 7; i++) {
		v1[i] = i;
	}
	for (int i = 0; i < 5; i++) {
		v2[i] = i;
	}
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5), v2(5);
	for (int i = 0; i < 5; i++) {
		v1[i] = i;
	}
	for (int i = 0; i < 5; i++) {
		v2[i] = i;
	}
	ASSERT_NO_THROW(v1 - v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(7), v2(5);
	for (int i = 0; i < 7; i++) {
		v1[i] = i;
	}
	for (int i = 0; i < 5; i++) {
		v2[i] = i;
	}
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5), v2(5);
	for (int i = 0; i < 5; i++) {
		v1[i] = i;
	}
	for (int i = 0; i < 5; i++) {
		v2[i] = i;
	}
	ASSERT_NO_THROW(v1 * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(7), v2(5);
	ASSERT_ANY_THROW(v1 * v2);
}


TEST(TDynamicVector, do_move)
{
	TDynamicVector<int> v1(5);
	int* tmp = v1.get_pMem();
	TDynamicVector<int> v2(std::move(v1));


	EXPECT_EQ(v1.size(), 0);
	EXPECT_EQ(v1.get_pMem(), nullptr);
	EXPECT_EQ(v2.size(), 5);
	EXPECT_EQ(v2.get_pMem(), tmp);
}



TEST(TDynamicVector, do_move_operator) {
	TDynamicVector<int> v1(10000);
	int* tmp = v1.get_pMem();
	TDynamicVector<int> v2 = std::move(v1);

	EXPECT_EQ(v1.size(), 0);
	EXPECT_EQ(v1.get_pMem(), nullptr);
	EXPECT_EQ(v2.size(), 10000);
	EXPECT_EQ(v2.get_pMem(), tmp);
	for (int i = 0; i < 10000; i++)
		ASSERT_EQ(0, tmp[i]);

}
