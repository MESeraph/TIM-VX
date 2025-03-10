/****************************************************************************
*
*    Copyright (c) 2022 Vivante Corporation
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
#include "tim/vx/ops/pool1d.h"

#include "builtin_op_impl.h"
#include "type_utils.h"
#include "vsi_nn_pub.h"

namespace tim {
namespace vx {
namespace ops {

// for Classic Pool1d
Pool1d::Pool1d(Graph* graph, PoolType type, PadType padding,
               uint32_t ksize, uint32_t stride, RoundType round_type,
               DataLayout layout)
    : BuiltinOp(graph, VSI_NN_OP_POOL, 1, 1, layout),
      type_(type),
      padding_(padding),
      ksize_(ksize),
      stride_(stride),
      round_type_(round_type),
      pad_({0,0}) {
  this->impl()->node()->nn_param.pool.type = TranslatePoolType(type_);
  this->impl()->node()->nn_param.pool.round_type =
      TranslateRoundType(round_type_);
  this->impl()->node()->nn_param.pool.ksize[0] = ksize_;
  this->impl()->node()->nn_param.pool.stride[0] = stride_;
  this->impl()->node()->nn_param.pool.pad_type = TranslatePadType(padding_);
  this->SetRoundingPolicy(OverflowPolicy::SATURATE, RoundingPolicy::RTNE, round_type_);
}

Pool1d::Pool1d(Graph* graph, PoolType type,
               const std::array<uint32_t, 2>& pad,
               uint32_t ksize,
               uint32_t stride, 
               RoundType round_type,
               DataLayout layout)
    : BuiltinOp(graph, VSI_NN_OP_POOL, 1, 1, layout),
      type_(type), padding_(PadType::AUTO), ksize_(ksize), stride_(stride),
      round_type_(round_type), pad_(pad) {
  Init();
}

// for Global Pool1d
Pool1d::Pool1d(Graph* graph, PoolType type,
               uint32_t input_size,
               RoundType round_type,
               DataLayout layout)
    : BuiltinOp(graph, VSI_NN_OP_POOL, 1, 1, layout),
      type_(type), padding_(PadType::AUTO), ksize_(input_size), stride_(input_size),
      round_type_(round_type), pad_({0, 0}) {
  Init();
}

// for Adaptive Pool1d
Pool1d::Pool1d(Graph* graph, PoolType type,
               uint32_t input_size,
               uint32_t output_size,
               RoundType round_type,
               DataLayout layout)
    : BuiltinOp(graph, VSI_NN_OP_POOL, 1, 1, layout),
      type_(type), padding_(PadType::AUTO),
      round_type_(round_type), pad_({0, 0}) {
  stride_ = floor(input_size / (float)(output_size));
  ksize_ = input_size - (output_size - 1) * stride_;
  Init();
}

void Pool1d::Init() {
  this->impl()->node()->nn_param.pool.type = TranslatePoolType(type_);
  this->impl()->node()->nn_param.pool.round_type =
      TranslateRoundType(round_type_);
  this->impl()->node()->nn_param.pool.ksize[0] = ksize_;
  this->impl()->node()->nn_param.pool.stride[0] = stride_;
  this->impl()->node()->nn_param.pool.pad[0] = pad_[0];
  this->impl()->node()->nn_param.pool.pad[1] = pad_[1];
  this->SetRoundingPolicy(OverflowPolicy::SATURATE, RoundingPolicy::RTNE, round_type_);
}

std::shared_ptr<Operation> Pool1d::Clone(std::shared_ptr<Graph>& graph) const {
  return graph->CreateOperation<Pool1d>(this->type_, this->pad_, this->ksize_,
                                        this->stride_, this->round_type_,
                                        this->impl_->layout_);
}

}  // namespace ops
}  // namespace vx
}  // namespace tim