//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://kylelutz.github.com/compute for more information.
//---------------------------------------------------------------------------//

//[copy_data_example

#include <vector>
#include <boost/compute.hpp>

int main()
{
    // create data array on host
    int host_data[] = { 1, 3, 5, 7, 9 };

    // create vector on device
    boost::compute::vector<int> device_vector(5);

    // copy from host to device
    boost::compute::copy(host_data,
                         host_data + 5,
                         device_vector.begin());

    // create vector on host
    std::vector<int> host_vector(5);

    // copy data back to host
    boost::compute::copy(device_vector.begin(),
                         device_vector.end(),
                         host_vector.begin());

    return 0;
}

//]
