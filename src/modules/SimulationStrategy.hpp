/*
 *  jrrs Copyright (C) 2007-2010 Kaveh Vahedipour
 *                               Forschungszentrum Jülich, Germany
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

#ifndef __SIMULATION_STRATEGY_HPP__
#define __SIMULATION_STRATEGY_HPP__

#define GAMMARAD 2.6753e3
#define TWOPI	 6.283185

#include "../common.h"
#include "Matrix.hpp"

namespace RRStrategy {
	
	/*
	 * @brief  Simulation package structure
	 */
	struct SimulationBundle {

		// Incoming
		Ptr< Matrix<cplx> >   tb1;  /**<! b1                   (target)    */ 
		Ptr< Matrix<cplx> >   sb1;  /**<!                      (sample)    */ 
		
		Ptr< Matrix<float> > agr;   /**<! Acquisition gradients            */ 
		
		Ptr< Matrix<float> > tr;    /**<! spatial vectors        (target)  */ 
		Ptr< Matrix<float> > sr;    /**<! */ 

		Ptr< Matrix<float> > tb0;   /**<! b0 maps                (target)  */ 
		Ptr< Matrix<float> > sb0;   /**<!                        (sample)  */ 

		Ptr< Matrix<cplx> >  tmxy;  /**<! starting magnetisation (target)  */
		Ptr< Matrix<float> > tmz;
		Ptr< Matrix<cplx> >  smxy;  /**<!                        (sample)  */
		Ptr< Matrix<float> > smz;

		Ptr< Matrix<float> > jac;   /**<! jacobian j(k(t))                 */

		int                  np;    /**<! # threads                        */
		int                  mode;  /**<! mode (0:single run, 1:iterative) */

		float                dt;    /**<! time step                        */
		float                cgeps; /**<! CGNR convergence criterium       */
		int                  cgit;  /**<! CGNR convergence criterium       */
		
		bool                 exc;   /**<! Excite?                          */
		bool                 v;     /**<! verbose                          */
		
		// Outgoing
		Ptr< Matrix<cplx> >  rf;   /**<! RF pulses                         */
		Ptr< Matrix<cplx> >  mxy;  /**<! Excited transverse magnetisation  */
		Ptr< Matrix<float> > mz;   /**<! Longitudinal magnetisation        */

		bool Dump (std::string odf) {
			
#ifdef HAVE_MAT_H	
			
			MATFile* mf = matOpen (odf.c_str(), "w");
			
			if (mf == NULL) {
				printf ("Error creating file %s\n", odf.c_str());
				return false;
			}
			
			sb1->MXDump  (mf, "sb1" );	
			tb1->MXDump  (mf, "tb1" );
			tr->MXDump   (mf, "tr"  );
			sr->MXDump   (mf, "sr"  );
			tb0->MXDump  (mf, "tb0" );
			sb0->MXDump  (mf, "sb0" );
			tmxy->MXDump (mf, "tmxy");
			tmz->MXDump  (mf, "tmz" );
			smxy->MXDump (mf, "smxy");
			smz->MXDump  (mf, "smz" );
			jac->MXDump  (mf, "jac" );
			rf->MXDump   (mf, "rf"  );
			mxy->MXDump  (mf, "mxy" );
			mz->MXDump   (mf, "mz"  );
			
			if (matClose(mf) != 0) {
				printf ("Error closing file %s\n", odf.c_str());
				return false;
			}
#endif
		}
		
	};

	/**
	 * @brief Base class for simulation stratgies used by direct method
 	 */
	class SimulationStrategy {		
		
	public:
		

		/**
		 * @brief       Construct with bundle
		 */
		SimulationStrategy  (SimulationBundle* sb) { m_sb = sb; }

		/**
		 * @brief       Default destructor
		 */
		virtual 
		~SimulationStrategy ()                     {};


		/**
		 * @brief       Piece-wise constant bloch simulation
		 */
		virtual void 
		Simulate  () = 0;

		
	protected: 
		
		SimulationStrategy  ()                    {};

		SimulationBundle* m_sb;

	};
		




}

#endif // SimulationStrategy
