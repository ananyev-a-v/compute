//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://kylelutz.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_LAMBDA_RESULT_OF_HPP
#define BOOST_COMPUTE_LAMBDA_RESULT_OF_HPP

#include <boost/mpl/vector.hpp>
#include <boost/proto/proto.hpp>

#include <boost/compute/type_traits/common_type.hpp>

namespace boost {
namespace compute {
namespace lambda {

namespace mpl = boost::mpl;
namespace proto = boost::proto;

// meta-function returning the result type of a lambda expression
template<class Expr,
         class Args = void,
         class Tags = typename proto::tag_of<Expr>::type>
struct result_of
{
};

// terminals
template<class Expr, class Args>
struct result_of<Expr, Args, proto::tag::terminal>
{
    typedef typename proto::result_of::value<Expr>::type type;
};

// binary operators
#define BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(tag) \
    template<class Expr, class Args> \
    struct result_of<Expr, Args, tag> \
    { \
        typedef typename proto::result_of::child_c<Expr, 0>::type left; \
        typedef typename proto::result_of::child_c<Expr, 1>::type right; \
        \
        typedef typename boost::common_type< \
            typename ::boost::compute::lambda::result_of< \
                         left, \
                         Args, \
                         typename proto::tag_of<left>::type>::type, \
            typename ::boost::compute::lambda::result_of< \
                         right, \
                         Args, \
                         typename proto::tag_of<right>::type>::type \
         >::type type; \
    };

BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::plus)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::minus)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::multiplies)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::divides)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::modulus)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::less)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::greater)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::less_equal)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::greater_equal)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::equal_to)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::not_equal_to)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::logical_and)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::logical_or)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::bitwise_and)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::bitwise_or)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::bitwise_xor)

// functions
template<class Expr, class Args>
struct result_of<Expr, Args, proto::tag::function>
{
    typedef typename proto::result_of::child_c<Expr, 0>::type func_expr;
    typedef typename proto::result_of::value<func_expr>::type func;

    typedef typename func::template lambda_result<Expr, Args>::type type;
};

} // end lambda namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_LAMBDA_RESULT_OF_HPP
