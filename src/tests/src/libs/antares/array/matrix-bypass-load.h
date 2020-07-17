

#ifndef __ANTARES_LIBS_ARRAY_MATRIX_BYPASS_LOAD_H__
# define __ANTARES_LIBS_ARRAY_MATRIX_BYPASS_LOAD_H__


#include<array/fill-matrix.h>

using namespace Yuni;

namespace Antares
{
	namespace UnitTests
	{
		struct PredicateIdentity
		{
			template<class U> inline U operator () (const U& value) const
			{
				return value;
			}
		};
	}
}

template<class T = double, class ReadWriteT = T>
class Matrix_load_bypass : public Matrix_easy_to_fill<T, ReadWriteT>
{
public:
	Matrix_load_bypass() :
		Matrix_easy_to_fill(),
		loadFromCSVFile_called(false)
	{};

	Matrix_load_bypass(uint height, uint width) :
		Matrix_easy_to_fill<T, ReadWriteT>(height, width),
		loadFromCSVFile_called(false)
	{};

	Matrix_load_bypass(uint height, uint width, const vector<T>& vec) :
		Matrix_easy_to_fill<T, ReadWriteT>(height, width, vec),
		loadFromCSVFile_called(false)
	{};

	virtual bool loadFromCSVFile(
		const AnyString& filename,
		uint minWidth, uint maxHeight,
		uint options = optNone,
		BufferType* buffer = NULL)
	{
		loadFromCSVFile_called = true;
		return true;
	}


public:
	bool loadFromCSVFile_called;
};


template<class T = double, class ReadWriteT = T>
class fake_fuffer_factory
{
public:
	fake_fuffer_factory() :
		buffer_precision_(0),
		buffer_print_dimensions_(false)
	{}

	~fake_fuffer_factory() {};

	void matrix_to_build_buffer_with(Matrix_easy_to_fill<T, ReadWriteT> * mtx) { mtx_to_build_buffer_with_ = mtx; }
	void set_precision(uint precision) { buffer_precision_ = precision; }
	void print_dimensions(bool print_dims) { buffer_print_dimensions_ = print_dims; }
	Clob* build_buffer()
	{
		Clob* buffer_to_return = new Clob;
		Antares::UnitTests::PredicateIdentity predicate;
		mtx_to_build_buffer_with_->saveToFileDescriptor(*buffer_to_return, buffer_precision_, buffer_print_dimensions_, predicate);

		return buffer_to_return;
	}

private:
	uint buffer_precision_;
	bool buffer_print_dimensions_;
	Matrix_easy_to_fill<T, ReadWriteT> * mtx_to_build_buffer_with_;

};


template<class T = double, class ReadWriteT = T>
class Matrix_mock_load_to_buffer : public Matrix<T, ReadWriteT>
{
public:
	Matrix_mock_load_to_buffer() :
		Matrix(),
		fake_mtx_error_when_loading_(IO::errNone)
	{};

	Matrix_mock_load_to_buffer(uint height, uint width) :
		Matrix<T, ReadWriteT>(height, width),
		fake_mtx_error_when_loading_(IO::errNone)
	{};

	Matrix_mock_load_to_buffer(uint height, uint width, const vector<T>& vec) :
		Matrix<T, ReadWriteT>(height, width, vec),
		fake_mtx_error_when_loading_(IO::errNone)
	{};
	
	virtual IO::Error loadFromFileToBuffer(BufferType & buffer, const AnyString& filename, uint64 hardlimit) const
	{
		return fake_mtx_error_when_loading_;
	}

	void error_when_loading_from_file(IO::Error err) { fake_mtx_error_when_loading_ = err; }

private:
	IO::Error fake_mtx_error_when_loading_;
};

#endif	// __ANTARES_LIBS_ARRAY_MATRIX_BYPASS_LOAD_H__