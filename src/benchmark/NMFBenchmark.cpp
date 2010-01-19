//
// This file is part of openBliSSART.
//
// Copyright (c) 2007-2009, Alexander Lehmann <lehmanna@in.tum.de>
//                          Felix Weninger <felix@weninger.de>
//                          Bjoern Schuller <schuller@tum.de>
//
// Institute for Human-Machine Communication
// Technische Universitaet Muenchen (TUM), D-80333 Munich, Germany
//
// openBliSSART is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 2 of the License, or (at your option) any later
// version.
//
// openBliSSART is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// openBliSSART.  If not, see <http://www.gnu.org/licenses/>.
//


#include "NMFBenchmark.h"

#include <blissart/nmf/Deconvolver.h>
#include <blissart/nmf/randomGenerator.h>

#include <iomanip>


using Poco::Timestamp;
using blissart::nmf::Deconvolver;
using blissart::linalg::Matrix;
using namespace std;


namespace benchmark {


void NMFBenchmark::run()
{
	Matrix v(500, 1000, blissart::nmf::gaussianRandomGenerator);

    // sparsity matrix
    Matrix s(20, 1000);
    for (unsigned int j = 0; j < s.cols(); ++j) {
        for (unsigned int i = 0; i < s.rows(); ++i) {
            s(i, j) = 0.1;
        }
    }

	// NMF, Euclidean distance,
	// 500x1000 Gaussian random matrix, 20 components
	// fixed number of iterations (100)
	{
		Deconvolver d(v, 20, 1);
		Timestamp start;
        d.decompose(Deconvolver::EuclideanDistance, 100, 0.0, this);
		Timestamp end;
		_elapsedTimes["NMF-ED 500x1000 r=20"] = end - start;
	}

    // NMF, KL divergence,
	// 500x1000 Gaussian random matrix, 20 components
	// fixed number of iterations (100)
	{
		Deconvolver d(v, 20, 1);
		Timestamp start;
        d.decompose(Deconvolver::KLDivergence, 100, 0.0, this);
		Timestamp end;
		_elapsedTimes["NMF-KL 500x1000 r=20"] = end - start;
	}

	// Sparse NMF, Euclidean distance,
	// 500x1000 Gaussian random matrix, 20 components
	// fixed number of iterations (100)
	{
		Deconvolver d(v, 20, 1);
		Timestamp start;
        d.decompose(Deconvolver::EuclideanDistanceSparse, 100, 0.0, this);
		Timestamp end;
		_elapsedTimes["SNMF-ED 500x1000 r=20"] = end - start;
	}

    // Sparse NMF, KL divergence,
	// 500x1000 Gaussian random matrix, 20 components
	// fixed number of iterations (100)
	{
		Deconvolver d(v, 20, 1);
		Timestamp start;
        d.decompose(Deconvolver::KLDivergenceSparse, 100, 0.0, this);
		Timestamp end;
		_elapsedTimes["SNMF-KL 500x1000 r=20"] = end - start;
	}
}


void NMFBenchmark::progressChanged(float progress)
{
	cout << "\r"
		 << fixed << setw(6) << setprecision(2)
		 << (progress * 100.0) << "% complete ...";
	if (progress == 1.0)
		cout << endl;
	cout << flush;
}


} // namespace benchmark
