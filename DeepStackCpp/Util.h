#pragma once
#include <unsupported/Eigen/CXX11/Tensor>
#include <Eigen/Dense>

using namespace Eigen;

#define edim(dimSlice) Eigen::array<int, 1> { { dimSlice} }

class Util
{
	public:
		static inline ArrayXXf ExpandAs(ArrayXXf data, ArrayXXf as)
		{
			//ToDo: remove during optimization for performance reasons
			float difCols = (float)as.cols() / data.cols();
			assert(difCols >= 1.0);
			assert(ceilf(difCols) == difCols && "The coefficients must be integers");

			float difRows = (float)as.rows() / data.rows();
			assert(difRows >= 1.0);
			assert(ceilf(difRows) == difRows && "The coefficients must be integers");

			ArrayXXf res = data.replicate(difRows, difCols);
			return res;
		}

		static inline ArrayXXf ExpandAs(ArrayXf data, ArrayXXf as)
		{
			return data.replicate(as.rows(), as.cols());
		}

		//static inline MatrixXf ExpandAs(MatrixXf data, MatrixXf as)
		//{
		//	return data.replicate(as.rows(), as.cols());
		//}

		static inline MatrixXf ExpandAs(VectorXf data, MatrixXf as)
		{
			return data.replicate(as.rows(), as.cols());
		}

		static inline void ClipLow(ArrayXXf& target, float lowLimin)
		{
			target = (target >= lowLimin).select(
				target,
				ArrayXXf::Constant(target.rows(), target.cols(), lowLimin)
			);
		}

		static inline void ClipLow(ArrayXf& target, float lowLimin)
		{
			target = (target >= lowLimin).select(
				target,
				ArrayXf::Constant(target.rows(), target.cols(), lowLimin)
			);
		}

		//static inline void ClipLow(MatrixXf& target, float lowLimin)
		//{
		//	target = (target.array() >= lowLimin).select(
		//		target,
		//		MatrixXf::Constant(target.rows(), target.cols(), lowLimin)
		//	);
		//}

		static inline void CopyTo(ArrayXXf & target, ArrayXXf & source)
		{
			assert(target.size() >= source.size());
			memcpy(target.data(), source.data(), source.size() * sizeof(float));
		}

		static inline TensorMap<Tensor<float, 2>> ToTensor(ArrayXXf & source)
		{
			return TensorMap<Tensor<float, 2>>(source.data(), source.rows(), source.cols());
		}

		//static inline TensorMap<Tensor<float, 2>> ToTensor(MatrixXf & source)
		//{
		//	return TensorMap<Tensor<float, 2>>(source.data(), source.rows(), source.cols());
		//}

		//static inline void CopyTo(MatrixXf & target, MatrixXf & source)
		//{
		//	assert(target.size() >= source.size());
		//	memcpy(target.data(), source.data(), source.size() * sizeof(float));
		//}

};