/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/Optimizer/CCGOptimizer.inl
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Optimized Search Implementation
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// CCGOptimizer implementation
inline CCGOptimizer * CCGOptimizer::GetInstance() {
	static CCGOptimizer * s_pInstance = NULL;
    if ( s_pInstance == NULL )
        s_pInstance = New() CCGOptimizer();
	return s_pInstance;
}

inline SearchParameters * CCGOptimizer::GetSearchParameters() {
    Assert( !m_bOptimizing );
    return &m_hSearchParams;
}

inline UInt CCGOptimizer::GetPermutationsCount() const {
    Assert( m_bOptimizing );
    return m_iPermutationsCount;
}
inline UInt CCGOptimizer::GetExploredPermutations() const {
    Assert( m_bOptimizing );
    return m_iExploredPermutation;
}

inline Bool CCGOptimizer::IsOptimizing() const {
    return m_bOptimizing;
}
