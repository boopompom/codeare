/*
 *  codeare Copyright (C) 2007-2010 Kaveh Vahedipour
 *                                  Forschungszentrum Juelich, Germany
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 *  02110-1301  USA
 */

#ifndef __CCSENSE_HPP__
#define __CCSENSE_HPP__

#include "Algos.hpp"
#include "CX.hpp"
#include "DFT.hpp"

/**
 * @brief SENSE: Sensitivity Encoding for Fast MRI<br/>
 *        MRM (1999): vol. 42 (5) pp. 952-962<br/>
 *        This operator acts of Cartesian k-space data
 */
template <class T>
class CSENSE : public FT<T> {
	
public:
	

	/**
	 * @brief          Default constructor
	 */
	CSENSE() : m_initialised (false) {};


	/**
	 * @brief          Construct CSENSE plans for forward and backward transform with credentials<br/>
	 *                 As of now we expect acceleration only in one direction
	 * 
	 * @param  sens    Sensitivity maps if imsize
	 * @param  af      Acceleration factor vector 2/3 elements for 2D/3D 
	 * @param  mask    K-Space mask
	 * @param  pc      Off-resonance maps if available (default empty)
	 * @param  b0      Phase correction applied before forward or after adjoint transforms (default: empty)
	 */
	CSENSE             (const Matrix< complex<T> >& sens, const Matrix<size_t>& af,
			            const Matrix<T>& mask = Matrix<T>(1), const Matrix<T>& pc = Matrix<T>(1),	
						const Matrix<T>& b0 = Matrix<T>(1));
		

	/**
	 * @brief          Clean up and destruct
	 */
	~CSENSE            () {
	}


	/**
	 * @brief          Forward transform
	 *
	 * @param  m       To transform
	 * @return         Transform
	 */
	Matrix<T> 
	Adjoint            (const Matrix<T>& m) const {
		
		Matrix<T> res;
		Matrix<T> s (m_nc,m_af[1]);
		Matrix<T> rp;
		Matrix<T> tmp;

		// FT individual channels
		/*
		for (size_t i = 0; i < m_dims[3]; i++) {

			if (m_ndim == 2) tmp = Slice  (m, i);
			else             tmp = Volume (m, i);

			tmp = m_dft ->* tmp;
			
			if (m_ndim == 2) Slice  (m,i,tmp);
			else             Volume (m,i,tmp);

		}
		*/
		// Antialias
		for (size_t x = 0; x < m_dims[0]; x++)
			for (size_t y = 0; y < m_dims[1]; y++) 
				for (size_t z = 0; z < m_dims[2]; z++) {

					for (size_t c = 0; c < m_dims[3]; c++) 
						for (size_t i = 0; i < m_af[1]; i ++) 
							s (c, i) = m_sens (c, y + m_dims[1] * i, x, z);
					
					// s=inv(s'*s)*s';
					//s = s.prodt (s);
					//s = inv (s);                
					//s = s.prod  (!s);
					
					// rp=si*imfold(:,y,x);
					// rp = m (y + m_dims[1], x);

					//for (size_t i = 0; i < m_af[1]; i++)
					//	res (y + m_dims[1] * i, x, z) = rp [i]; 

				}

		return res;
		
	}

	
	/**
	 * @brief          Backward transform (SENSE backward trafo? I don't know!)<br/> Bloedsinn!
	 *                 Why would anyone want to go back to sensitivity weightes undersampled k-space data?
	 *
	 * @param  m       To transform
	 * @return         Bummer! (This is not nice, right?)
	 */
	Matrix<T> 
	Trafo             (const Matrix<T>& m) const {
		
		assert (false);


	}


private:

	DFT<T>*        m_dft;

	Matrix<T>      m_b0;

	Matrix< std::complex<T> > m_sens;
	Matrix< std::complex<T> > m_pc;
	
	Matrix<size_t> m_af;
	
	size_t         m_ndim;
	Matrix<size_t> m_dims; /**< Operator dimensionality Valid: [2,3]*/
	size_t         m_nc;

	bool           m_initialised;

};

template<>
CSENSE<float>::CSENSE (const Matrix<cxfl>& sens, const Matrix<size_t>& af,
					   const Matrix<float>& mask, const Matrix<float>& pc, 
					   const Matrix<float>& b0) {
	
	// We expect 4D sensitivities [X,Y,Z,C]
	//m_dims = size(sens);
	m_ndim = (m_dims[2] == 1) ? 2 : 3;

	Matrix<size_t> ftdims (m_ndim,1);
	for (size_t i = 0; i < m_ndim; i++)
		ftdims[i] = m_dims[i];

	m_dft  = new DFT<float> (ftdims, mask, pc);
	
    //Matrix<bool> isf = isinf (sens);

	//m_sens = sens;
	//m_af   = af;
	//m_pc   = pc;
	
}

#endif
