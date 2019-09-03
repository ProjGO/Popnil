#ifndef _SUNGTK_INTERFACE_H_
#define _SUNGTK_INTERFACE_H_

#include<gtk/gtk.h>


#define GET_WIDGET_WIDTH(widget)	widget->allocation.width	//widget���
#define GET_WIDGET_HEIGHT(widget)	widget->allocation.height	//widget�߶�

extern int sungtk_background_set_picture(GtkWidget *widget, const gchar *path, const int w, const int h);


/**************************************************
 * ��������:�������õ�image�������һ��ͼƬ
 * ��������:
 *				image:�Ѵ����õ�image�ؼ�
 * 				file_path:ͼƬ·��
 *				 w��h:ͼƬ���ȺͿ������w==0&&h==0,��ʹ��ͼƬĬ�ϴ�С
 * ��������:�ɹ�����0,ʧ�ܷ���-1
 * ά����¼:2013-12-18 by lihuibo
 **************************************************/
extern int sungtk_image_load_picture(GtkWidget *image, const char *file_path, const int w, const int h );

/**************************************************
 * ��������:����һ����ͼƬ��image�ؼ�
 * ��������:
 *				image:�Ѵ����õ�image�ؼ�
 * 				file_path:ͼƬ·��
 *				 w��h:ͼƬ���ȺͿ������w==0&&h==0,��ʹ��ͼƬĬ�ϴ�С
 * ��������:�ɹ�����0,ʧ�ܷ���-1
 * ά����¼:2013-12-18 by lihuibo
 **************************************************/
GtkWidget *sungtk_image_new_from_file(const char *file_path, const int w, const int h);


/**************************************************
 * ��������:����ͼƬ·������һ���°�ť��ͬʱָ��ͼƬ��С
 * ��������:
 * 				file_path:ͼƬ·��
 * 				w��h:ͼƬ���ȺͿ������w==0&&h==0,��ʹ��ͼƬĬ�ϴ�С
 * ��������:�ɹ����ش���button��ַ
 * ά����¼:2013-12-18 by lihuibo
 **************************************************/
extern GtkWidget *sungtk_button_new_with_image(const char *file_path, const int w, const int h);

/**************************************************
 * ��������:�������ð�ť����Ƭ
 * ��������:button:Ҫ���õİ�ť�ؼ�
 * 				file_path:ͼƬ·��
 * 				w��h:ͼƬ���ȺͿ������w==0&&h==0,��ʹ��ͼƬĬ�ϴ�С
 * ��������:
 * ά����¼:2013-12-18 by lihuibo
 **************************************************/
extern int sungtk_button_set_image(GtkWidget *button, const gchar *file_path, const int w, const int h);


extern GtkWidget *sungtk_button_new_with_label_and_image(const char *file, const char *label, const int w, const int h);


/**************************************************
 * ��������: ���ÿؼ������С
 * ��������:
 * 				widget: ��Ҫ�ı�����Ŀؼ�
 * 				size: �����С
 *				is_button: TRUE����ؼ�Ϊ��ť��FALSEΪ�����ؼ�
 * ��������:�ɹ�����0��ʧ�ܷ���-1
 * ά����¼:2013-12-18 by lihuibo
 **************************************************/
extern int sungtk_widget_set_font_size(GtkWidget *widget, int size, gboolean is_button);

/***********************************************
* ��������:��ȡһ��GdkColor����
* ��������:color_buf:����������ɫ����"red"��"blue"
				color:���GdkColor���͵�ַ
* ��������:�ɹ�����0��ʧ�ܷ���-1
* ά����¼:2013-12-18 by lihuibo
***********************************************/
extern int sungtk_color_get(const char *color_buf, GdkColor *color);

/***********************************************
* ��������:���ÿؼ�������ɫ
* ��������:widget:��Ҫ�ı���ɫ�Ŀؼ�
				color_buf:����������ɫ����"red"��"blue"
				is_button:�Ƿ�Ϊbutton
* ��������:�ɹ�����0��ʧ�ܷ���-1
* ά����¼:2013-12-18 by lihuibo
***********************************************/
extern int sungtk_widget_set_font_color(GtkWidget *widget, const char *color_buf, gboolean is_button);

/***********************************************
* ��������:����һ����������
* ��������:
* ��������:�ɹ�����0��ʧ�ܷ���-1
* ά����¼:2013-12-18 by lihuibo
***********************************************/
extern GtkWidget *sungtk_scrolled_window_new(void);

/***********************************************
* ��������:���ù������ڵ�ˮƽֵ
* ��������:widget:�������ڵ�ַ
				add_val:ԭ����֮�Ͻ�����ӣ�����ֵ�����෴����
* ��������:�ɹ�����0��ʧ�ܷ���-1
* ά����¼:2013-12-18 by lihuibo
***********************************************/
extern int sungtk_scrolled_window_set_hadjustment_value(GtkWidget *s_window, const gdouble add_val);

/***********************************************
* ��������:���ù������ڵĴ�ֱ����ֵ
* ��������:widget:�������ڵ�ַ
				add_val:ԭ����֮�Ͻ�����ӣ�����ֵ�����෴����
* ��������:�ɹ�����0��ʧ�ܷ���-1
* ά����¼:2013-12-18 by lihuibo
***********************************************/
extern int sungtk_scrolled_window_set_vadjustment_value(GtkWidget *s_window, const gdouble add_val);



/************************�Զ����б�************************************/
//ÿһ�е��ʱ�Ļص���������
typedef gboolean (*SunGtkSelectRow)(GtkWidget *widget, GdkEventButton *event, gpointer data);

//Ϊ�б���������Ľṹ��
typedef struct _clist_link
{
    GtkWidget *box;
    GtkWidget *head_box;
    GtkWidget *name_box;
    GtkWidget *event_box;	//每一行都有一个事件盒子，用于支持点击
    GtkWidget *label;		//将label放置在事件盒子中，用于显示文字
    GtkWidget *image;
    GtkWidget *name;
    GtkWidget *table;
    struct _clist_link *next;
}CListLink;

//�����б�Ľṹ��
typedef struct _sungtk_clist
{
	GtkWidget *fixed;		//�����б���һ���̶�����
	GtkWidget *vbox;		//���ô�ֱ���֣����Զ�̬׷����
	gint select_row;		//��ǰѡ����
	gint font_size;			//�����С
	gchar font_color[30];	//������ɫ
	gint row_height;		//ÿ�еĸ߶�
	gint col_width;			//ÿ�п��
	gint total_num;			//������
	gchar sig_str[30];		//�ź�
	SunGtkSelectRow callback;//�е���ص�����
	CListLink *head;
}SunGtkCList;

#define SUNGTK_CLIST(x) (SunGtkCList *)x	

//�Զ����б���
extern SunGtkCList *sungtk_clist_new();

//�б��ͷ���Դ
extern int sungtk_clist_unref(SunGtkCList *clist);

//׷��һ��
extern int sungtk_clist_append(SunGtkCList *clist, const gchar *text, const gchar *image, const gchar* name);

//����ǰ����ɫ
extern int sungtk_clist_set_foreground(SunGtkCList *clist, const gchar *color_buf);

//��������һ�е���ɫ
extern int sungtk_clist_set_row_color(SunGtkCList *clist, gint row, const gchar *color_buf);

//ѡ��ĳһ��
extern int sungtk_clist_select_row(SunGtkCList *clist, gint row, const gchar *color_buf);

//�����и߶�
extern int sungtk_clist_set_row_height(SunGtkCList *clist, gint height);

//�����п��
extern int sungtk_clist_set_col_width(SunGtkCList *clist, gint width);

//���������С
extern int sungtk_clist_set_text_size(SunGtkCList *clist, int size);

//��ȡĳһ������
extern const gchar *sungtk_clist_get_row_data(SunGtkCList *clist, gint row);

//����ĳһ������
extern int sungtk_clist_set_row_data(SunGtkCList *clist, gint row, const gchar *text);

//���õ���е��ź�
extern int sungtk_clist_set_select_row_signal(SunGtkCList *clist, const gchar *detailed_signal, SunGtkSelectRow callback);

//���������б����ڹ̶����ֵ�λ��
extern void sungtk_clist_set_position_in_fixed(SunGtkCList *clist, gint x, gint y);

/**************************************************************************/




/*********************�Զ��廬����***************************************/

#define MOTIONKEY_NUM 9	//���ĸ���

//������̧��ʱ�ص������ĵ�����
typedef gboolean (*SunGtkMotionLockRelease)(GtkWidget *widget, GdkEventButton *event, gpointer data);

//�����������Ľṹ��
typedef struct _motion_lock
{
	GtkWidget *event_box;	//�����¼�����
	GtkWidget *fixed;		//�¼�������ӹ̶�����
	GtkWidget *image[MOTIONKEY_NUM];	//ͼƬ�ؼ�
	gint password[MOTIONKEY_NUM];		//�����¼
	gint pressed[MOTIONKEY_NUM];		//ÿ��ͼƬ�Ƿ��԰���
	gint start_flag;		//��һ�ΰ��±�־λ
	
	gint lock_size;			//�����������Ĵ�С
	gint img_size;			//ÿ��ͼƬ��С
	gint space_size;		//ͼƬ��ļ��
	gchar *press_pic;		//������Ƭ·��
	gchar *unpress_pic;		//δ������Ƭ·��
}SungtkMotionLock;

//������̧��ʱ�Ĵ���
extern void sungtk_motion_lock_release_deal(SungtkMotionLock *lock);

//���û�����̧��ʱִ�еĻص������� ʵ�ʾ����¼�����̧���¼�
extern void sungtk_motion_lock_signal_release(SungtkMotionLock *lock, SunGtkMotionLockRelease callback_release);

//��ȡ���������µ�ֵ
extern void sungtk_motion_lock_get_password(SungtkMotionLock *lock, char *pwd, int size);

//�������Ĵ�������Ҫָ����С����ͼƬ·����
extern SungtkMotionLock *sungtk_motion_lock_new(gint lock_size, gint img_size, const gchar *press_pic, const gchar *unpress_pic);

//��������Դ�ͷ�
extern void sungtk_motion_lock_unref(SungtkMotionLock *lock);
/**************************************************************************/


#endif


