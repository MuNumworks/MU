#ifndef POINCARE_COSINE_H
#define POINCARE_COSINE_H

#include <poincare/approximation_helper.h>
#include <poincare/expression.h>
#include <poincare/trigonometry.h>

namespace Poincare {

class CosineNode final : public ExpressionNode  {
public:

  // TreeNode
  size_t size() const override { return sizeof(CosineNode); }
  int numberOfChildren() const override;
#if POINCARE_TREE_LOG
  virtual void logNodeName(std::ostream & stream) const override {
    stream << "Cosine";
  }
#endif

  // Properties
  Type type() const override { return Type::Cosine; }
  float characteristicXRange(Context & context, Preferences::AngleUnit angleUnit) const override;

  template<typename T> static Complex<T> computeOnComplex(const std::complex<T> c, Preferences::AngleUnit angleUnit = Preferences::AngleUnit::Radian);

private:
  // Layout
  Layout createLayout(Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override;
  int serialize(char * buffer, int bufferSize, Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override;
  // Simplication
  Expression shallowReduce(Context & context, Preferences::AngleUnit angleUnit, bool replaceSymbols = true) override;
  // Evaluation
  Evaluation<float> approximate(SinglePrecision p, Context& context, Preferences::AngleUnit angleUnit) const override {
    return ApproximationHelper::Map<float>(this, context, angleUnit,computeOnComplex<float>);
  }
  Evaluation<double> approximate(DoublePrecision p, Context& context, Preferences::AngleUnit angleUnit) const override {
    return ApproximationHelper::Map<double>(this, context, angleUnit, computeOnComplex<double>);
  }
};

class Cosine final : public Expression {
public:
  Cosine();
  Cosine(const CosineNode * n) : Expression(n) {}
  explicit Cosine(Expression operand) : Cosine() {
    replaceChildAtIndexInPlace(0, operand);
  }
  static const char * Name() { return "cos"; }
  static const int NumberOfChildren() { return 1; }

  Expression shallowReduce(Context & context, Preferences::AngleUnit angleUnit, bool replaceSymbols = true);
};

}

#endif
