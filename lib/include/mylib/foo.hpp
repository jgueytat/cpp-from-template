//
// Copyright (c) 2021 Alexander Sacharov <a.sacharov@gmx.de>
//               All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.
//

#ifndef FOO_HH_B8E1D79912BD40CA9C1802D3D29894ED
#define FOO_HH_B8E1D79912BD40CA9C1802D3D29894ED

//-----------------------------------------------------------------------------
// includes <...>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes "..."
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Public defines and macros
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Public typedefs, structs, enums, unions and variables
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Public Function Prototypes
//----------------------------------------------------------------------------

namespace mylib {

   //
   /// Class CFooTest implements test methods
   /// @author Alexander Sacharov <as@asoft-labs.de>
   /// @date 2021-06-20
   //
   class CFooTest {
      // private variables

   public:
      /** constructor */
      CFooTest() = default;

      /** deallocate */
      ~CFooTest() = default;

      /// \brief test
      void Test();
   };

} // namespace mylib

#endif // FOO_HH_B8E1D79912BD40CA9C1802D3D29894ED
