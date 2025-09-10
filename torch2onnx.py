import torch
import onnx
import onnxruntime

import numpy as np

import funs
import funs.model as model


config = funs.load_yaml('./config.yaml')

funs.set_seed(config.seed)

# name setting
torch_model_name = 'FRFconv-TDS_overlapX'
onnx_model_name = 'FRFconv-TDS_onnx'

# 모델 정의
FRFconv_TDS = model.Mynet2(n_classes=8)

# 모델 가중치 로드
model_path = f'{config.model_root}/{torch_model_name}.pt'
FRFconv_TDS.load_state_dict(torch.load(model_path, weights_only=True))

# 모델을 추론 모드로 전환
FRFconv_TDS.eval()

# 모델에 대한 입력값
x = torch.randn(128, 1, 2048, requires_grad=True)
torch_out = FRFconv_TDS(x)

# 모델 변환
torch.onnx.export(FRFconv_TDS,               # 실행될 모델
                  x,                         # 모델 입력값 (튜플 또는 여러 입력값들도 가능)
                  f"{config.model_root}/{onnx_model_name}.onnx",   # 모델 저장 경로 (파일 또는 파일과 유사한 객체 모두 가능)
                  export_params=True,        # 모델 파일 안에 학습된 모델 가중치를 저장할지의 여부
                  opset_version=None,          # 모델을 변환할 때 사용할 ONNX 버전
                  do_constant_folding=True,  # 최적화시 상수폴딩을 사용할지의 여부
                  input_names = ['input'],   # 모델의 입력값을 가리키는 이름
                  output_names = ['output'], # 모델의 출력값을 가리키는 이름
                  dynamic_axes={'input' : {0 : 'batch_size'},    # 가변적인 길이를 가진 차원
                                'output' : {0 : 'batch_size'}})


# 모델 검증
onnx_model = onnx.load(f"{config.model_root}/{onnx_model_name}.onnx")
onnx.checker.check_model(onnx_model)

ort_session = onnxruntime.InferenceSession(f"{config.model_root}/{onnx_model_name}.onnx", providers=["CPUExecutionProvider"])

def to_numpy(tensor):
    return tensor.detach().cpu().numpy() if tensor.requires_grad else tensor.cpu().numpy()

# ONNX 런타임에서 계산된 결과값
ort_inputs = {ort_session.get_inputs()[0].name: to_numpy(x)}
ort_outs = ort_session.run(None, ort_inputs)

# ONNX 런타임과 PyTorch에서 연산된 결과값 비교
np.testing.assert_allclose(to_numpy(torch_out), ort_outs[0], rtol=1e-03, atol=1e-05)

print("Exported model has been tested with ONNXRuntime, and the result looks good!")