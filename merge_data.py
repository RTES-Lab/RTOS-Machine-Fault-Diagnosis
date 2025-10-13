import os
import shutil

# --- 설정 변수 ---
SOURCE_DIR_NAME = '1013_Class'
TARGET_DIR_NAME = 'data_st'

# 처리할 클래스 목록
CLASSES = ['H', 'L', 'M1', 'M2', 'M3', 'U1', 'U2', 'U3']

print(f"작업 시작: {SOURCE_DIR_NAME} -> {TARGET_DIR_NAME}")

for class_name in CLASSES:
    source_path = os.path.join(SOURCE_DIR_NAME, class_name)
    target_path = os.path.join(TARGET_DIR_NAME, class_name)
    
    # 1. 원본 디렉토리 확인
    if not os.path.isdir(source_path):
        print(f"⚠️  경고: 원본 디렉토리 '{source_path}'를 찾을 수 없습니다. 건너뜁니다.")
        continue

    if not os.path.isdir(target_path):
        print(f"📁 '{target_path}'가 존재하지 않아 생성합니다.")
        os.makedirs(target_path, exist_ok=True)
    
    # 2. 기존 타깃 폴더 내 파일 개수 확인 → 새 번호의 시작 기준
    existing_files = [
        f for f in os.listdir(target_path)
        if f.endswith('.txt') and os.path.isfile(os.path.join(target_path, f))
    ]
    # 기존 번호 중 최대값 찾기 (없으면 0)
    existing_indices = []
    for f in existing_files:
        try:
            num = int(f.rsplit('_', 1)[1].split('.')[0])
            existing_indices.append(num)
        except Exception:
            continue
    start_index = max(existing_indices, default=0) + 1

    # 3. 원본 파일 목록 가져와 정렬
    file_list = [
        f for f in os.listdir(source_path)
        if f.endswith('.txt') and os.path.isfile(os.path.join(source_path, f))
    ]

    def sort_key(filename):
        try:
            return int(filename.rsplit('_', 1)[1].split('.')[0])
        except Exception:
            return filename

    file_list.sort(key=sort_key)
    
    if not file_list:
        print(f"ℹ️  '{source_path}'에 처리할 .txt 파일이 없습니다.")
        continue
        
    print(f"\n--- 클래스: {class_name} ---")
    print(f"기존 파일: {len(existing_files)}개 / 새로 이동할 파일: {len(file_list)}개")
    print(f"새 파일 번호 범위: {start_index} ~ {start_index + len(file_list) - 1}")

    # 4. 파일 이동 및 이름 변경
    for i, old_filename in enumerate(file_list, start=start_index):
        base_name_parts = old_filename.rsplit('_', 1)
        if len(base_name_parts) < 2 or not base_name_parts[1].endswith('.txt'):
            print(f"⚠️  비정상적인 파일명 포맷 감지: {old_filename} (건너뜀)")
            continue

        base_prefix = base_name_parts[0]
        new_filename = f"{base_prefix}_{i}.txt"
        
        old_file_path = os.path.join(source_path, old_filename)
        new_file_path = os.path.join(target_path, new_filename)
        
        try:
            shutil.move(old_file_path, new_file_path)
        except Exception as e:
            print(f"❌ 오류: 파일 이동 실패 ({old_filename} → {new_filename}): {e}")

    print(f"✅ {class_name} 클래스 처리 완료.\n")

print("\n🎉 모든 클래스 파일 이동 및 번호 재지정 완료!")
