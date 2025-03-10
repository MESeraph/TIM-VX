/****************************************************************************
*
*    Copyright (c) 2021 Vivante Corporation
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
#ifndef TIM_VX_OPS_DECONV1D_H_
#define TIM_VX_OPS_DECONV1D_H_

#include <array>

#include "tim/vx/builtin_op.h"

namespace tim {
namespace vx {
namespace ops {

/**
 * ## DeConv1d
 *
 * Performs the transpose of 1-D convolution operation.
 *
 * This operation is sometimes called "deconvolution1d" after Deconvolutional Networks,
 * but is actually the transpose (gradient) of Conv2D rather than an actual deconvolution.
 *
 * - weights : the channel number for weight tensor.
 * - ksize : the length for weight tensor.
 * - padding : AUTO, VALID or SAME.
 * - pad : pad value for each spatial axis.
 * - stride : stride along each spatial axis.
 * - output_padding : specifying the amount of padding along the height and width of
 * the output tensor.
 */

class DeConv1d : public BuiltinOp {
  public:
    DeConv1d(Graph* graph, PadType pad_type,
        uint32_t stride, uint32_t output_padding, uint32_t group = 1,
        DataLayout input_layout = DataLayout::WHCN,
        DataLayout kernel_layout = DataLayout::WHIcOc);
    DeConv1d(Graph* graph, const std::array<uint32_t, 2>& pad,
        uint32_t stride, uint32_t output_padding, uint32_t group = 1,
        DataLayout input_layout = DataLayout::WHCN,
        DataLayout kernel_layout = DataLayout::WHIcOc);
    DeConv1d(Graph* graph, int32_t oc_count_, PadType pad_type,
        uint32_t ksize,
        uint32_t stride,
        uint32_t output_padding);
    DeConv1d(Graph* graph, int32_t oc_count_, PadType pad_type,
        uint32_t ksize,
        uint32_t stride,
        uint32_t output_padding,
        const std::array<uint32_t, 2>& pad,
        uint32_t group = 1);
    DeConv1d(Graph* graph, PadType pad_type,
        uint32_t stride, uint32_t output_padding,
        const std::array<uint32_t, 2>& pad, uint32_t group,
        DataLayout input_layout, DataLayout kernel_layout);

   std::shared_ptr<Operation> Clone(std::shared_ptr<Graph>& graph) const override;

  protected:
    const uint32_t oc_count_; // output channel count
    const PadType pad_type_;
    const uint32_t ksize_;
    const uint32_t stride_;
    const uint32_t output_padding_;
    const std::array<uint32_t, 2> pad_;
    const uint32_t group_;
    const DataLayout kernel_layout_;
};

} // namespace ops
} // namespace vx
} // namespace tim

#endif /* TIM_VX_OPS_DECONV1D_H_ */
