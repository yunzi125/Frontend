Rect detect_lip(Point2d face_center, Rect face) {

	Point2d lip_center = face_center + Point2d(0, face.height*0.32);
	Point2d gap_size(face.width * 0.18, face.height * 0.1);

	Point  lip_start = lip_center - gap_size;
	Point  lip_end = lip_center + gap_size;

	return Rect(lip_start, lip_end);
}

void  detect_hair(Point2d face_center, Rect face, vector<Rect> &hair_rect)
{
	Point2d  h_gap(face.width *0.45, face.height*0.65);	// �����̵� �Ÿ�
	Point2d  pt1 = face_center - h_gap;				// ���� ��� �����̵�
	Point2d  pt2 = face_center + h_gap;				// ������ �ϴ� �����̵�
	Rect   hair(pt1, pt2);				// ��ü �Ӹ�����

	Size  size(hair.width, hair.height * 0.40);	// ���Ӹ� �� �͹ظӸ� ũ��
	Rect  hair1(hair.tl(), size);					// ���Ӹ� ����
	Rect  hair2(hair.br() - (Point)size, size);	// �͹ظӸ� ����
								
	hair_rect.push_back(hair1);		// Rect�� ���Ϳ� ����
	hair_rect.push_back(hair2);
	hair_rect.push_back(hair);		// ��ü�Ӹ������� �������� ����
}
