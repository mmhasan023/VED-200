// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� _EXPORTS ��ȣ��
// �����ϵǸ�, ������ DLL�� ����ϴ� �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// BLACKFRAME_API �Լ��� DLL���� �������� ������ ����, �� DLL��
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.
#ifdef BLACKFRAME_EXPORTS
#define BLACKFRAME_API __declspec(dllexport)
#else
#define BLACKFRAME_API __declspec(dllimport)
#endif

// �� Ŭ������ BlackFrame.dll���� ������ ���Դϴ�.
class BLACKFRAME_API CBlackFrame {
public:
	CBlackFrame(void);
	// TODO: ���⿡ �޼��带 �߰��մϴ�.
};

extern BLACKFRAME_API int nBlackFrame;

BLACKFRAME_API int fnBlackFrame(void);
