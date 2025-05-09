/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006, 2007 Jonas Latt, Davide Dapelo
 *  E-mail contact: info@openlb.net
 *  The most recent release of OpenLB can be downloaded at
 *  <http://www.openlb.net/>
 *
 *  Generic collision, which modifies the particle distribution
 *  functions, implemented by Orestis Malaspinas, 2007
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
*/

#ifndef FD_NO_PENETRATION_BOUNDARY_POST_PROCESSORS_3D_H
#define FD_NO_PENETRATION_BOUNDARY_POST_PROCESSORS_3D_H

namespace olb {

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Postprocessor to treat no-penetration boundaries in the finite-difference advection-diffusion external field.
 */
template<typename T, typename DESCRIPTOR, typename FIELD=descriptors::AD_FIELD, typename SOURCE=void>
class FdBoundaryPostProcessor3D final : public FdBasePostProcessor3D<T,DESCRIPTOR,FIELD,SOURCE> {
public:
  FdBoundaryPostProcessor3D ( int x0, int x1, int y0, int y1, int z0, int z1, std::size_t& iT, int normalX, int normalY, int normalZ,
      std::shared_ptr<FdModel<T,DESCRIPTOR>> model, std::shared_ptr<fd::AdBoundarySchemeBase<3,T>> boundaryScheme );
  FdBoundaryPostProcessor3D ( std::size_t& iT, int normalX, int normalY, int normalZ,
      std::shared_ptr<FdModel<T,DESCRIPTOR>> model, std::shared_ptr<fd::AdBoundarySchemeBase<3,T>> boundaryScheme );
  int extent() const override
  {
    return 2;
  }
  int extent(int whichDirection) const override
  {
    return 2;
  }
  void process(BlockLattice<T,DESCRIPTOR>& blockLattice) override;
  void processSubDomain ( BlockLattice<T,DESCRIPTOR>& blockLattice,
                          int x0, int x1, int y0, int y1, int z0, int z1 ) override;
private:
  int _x0, _x1, _y0, _y1, _z0, _z1;
  int _normalX, _normalY, _normalZ;
  std::shared_ptr<FdModel<T,DESCRIPTOR>> _model;
  std::shared_ptr<fd::AdBoundarySchemeBase<3,T>> _boundaryScheme;
  std::vector<std::vector<T>> f, F, fNormal, fGhost;
};

template<typename T, typename DESCRIPTOR, typename FIELD=descriptors::AD_FIELD, typename SOURCE=void>
class FdBaseBoundaryPostProcessorGenerator3D : public FdBasePostProcessorGenerator3D<T,DESCRIPTOR,FIELD,SOURCE> {
public:
  FdBaseBoundaryPostProcessorGenerator3D(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
      std::size_t& iT, int normalX, int normalY, int normalZ,
      std::shared_ptr<FdModel<T,DESCRIPTOR>> model, std::shared_ptr<fd::AdBoundarySchemeBase<3,T>> boundaryScheme);
  FdBaseBoundaryPostProcessorGenerator3D(size_t& iT, int normalX, int normalY, int normalZ,
      std::shared_ptr<FdModel<T,DESCRIPTOR>> model, std::shared_ptr<fd::AdBoundarySchemeBase<3,T>> boundaryScheme );
  PostProcessor3D<T,DESCRIPTOR>* generate() const override;
private:
  int _normalX, _normalY, _normalZ;
  std::shared_ptr<FdModel<T,DESCRIPTOR>> _model;
  std::shared_ptr<fd::AdBoundarySchemeBase<3,T>> _boundaryScheme;
};

template<typename T, typename DESCRIPTOR, typename SCHEME_ADV, typename FIELD=descriptors::AD_FIELD, typename SOURCE=void>
class FdNeumannZeroBoundaryPostProcessorGenerator3D final : public FdBaseBoundaryPostProcessorGenerator3D<T,DESCRIPTOR,FIELD,SOURCE> {
public:
  FdNeumannZeroBoundaryPostProcessorGenerator3D(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
      std::size_t& iT, int normalX, int normalY, int normalZ, std::shared_ptr<FdModel<T,DESCRIPTOR>> model);
  FdNeumannZeroBoundaryPostProcessorGenerator3D(size_t& iT, int normalX, int normalY, int normalZ, std::shared_ptr<FdModel<T,DESCRIPTOR>> model);
  PostProcessorGenerator3D<T,DESCRIPTOR>* clone() const override;
};

}

#endif
