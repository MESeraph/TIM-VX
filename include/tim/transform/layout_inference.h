/****************************************************************************
 *
 *    Copyright (c) 2020 Vivante Corporation
 *
 *    Permission is hereby granted, free of charge, to any person obtaining a
 *    copy of this software and associated documentation files (the "Software"),
 *    to deal in the Software without restriction, including without limitation
 *    the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *    and/or sell copies of the Software, and to permit persons to whom the
 *    Software is furnished to do so, subject to the following conditions:
 *
 *    The above copyright notice and this permission notice shall be included in
 *    all copies or substantial portions of the Software.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *    DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/
#ifndef TIM_LAYOUT_INFERENCE_H_
#define TIM_LAYOUT_INFERENCE_H_

#include <map>
#include <vector>


namespace tim {

namespace vx {
    class Context;
    class Graph;
    class Tensor;
    class Operation;
}

namespace transform {
class IPermuteVector;
std::pair<
    /*graph after layout inference*/
    std::shared_ptr<vx::Graph>,
    /* tensor mapping between original graph and graph after layout infer*/
    std::map<std::shared_ptr<vx::Tensor>, std::shared_ptr<vx::Tensor>>>
LayoutInference(
    const std::shared_ptr<vx::Graph>& src_graph,
    std::shared_ptr<vx::Context>& ctx,
    std::map<std::shared_ptr<vx::Tensor>, std::shared_ptr<IPermuteVector>>
        tensor_pv_map = std::map<std::shared_ptr<vx::Tensor>,
                                 std::shared_ptr<IPermuteVector>>());

}  // namespace transform
}  // namespace tim

#endif