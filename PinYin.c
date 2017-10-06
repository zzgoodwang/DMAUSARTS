/******************** ��Ȩ���� ������ҵ��ѧ�����о��� �˽� ********************
* �ļ���             : main.c
* ����               : �˽�
* �汾               : V1.2
* ����               : 1/12/2010
* ����               : Main program body
* ����               ��������ʾFAT�ļ�ϵͳ					   				   	
*******************************************************************************/
#include "stm32f10x.h"
#include "PinYinIndex.c"
//ƴ����ϵĺ����ֿ�
//ƴ�������Ľṹ��
const struct PinYinPCB{
const char *PYSerList;  		//ƴ�������ַ�
const char *PYRankOneList;  	//���������ƴ����ϵĺ����ֿ��ָ��
};
const char PY_MB_a[]     ={"����"};
const char PY_MB_ai[]    ={"��������������������������"};
const char PY_MB_an[]    ={"������������������"};
const char PY_MB_ang[]   ={"������"};
const char PY_MB_ao[]    ={"�������������°İ�"};
const char PY_MB_ba[]    ={"�˰ͰȰǰɰṴ̋ưʰΰϰѰаӰְհ�"};
const char PY_MB_bai[]   ={"�װٰ۰ذڰܰݰ�"};
const char PY_MB_ban[]   ={"�����߰����������"};
const char PY_MB_bang[]  ={"������������������"};
const char PY_MB_bao[]   ={"������������������������������������"};
const char PY_MB_bei[]   ={"������������������������������"};
const char PY_MB_ben[]   ={"����������"};
const char PY_MB_beng[]  ={"�����±ñű�"};
const char PY_MB_bi[]    ={"�ƱǱȱ˱ʱɱұرϱձӱѱݱбֱԱͱױ̱αڱܱ�"};
const char PY_MB_bian[]  ={"�߱�ޱ���������"};
const char PY_MB_biao[]  ={"�����"};
const char PY_MB_bie[]   ={"�����"};
const char PY_MB_bin[]   ={"����������"};
const char PY_MB_bing[]  ={"������������������"};
const char PY_MB_bo[]    ={"����������������������������������������"};
const char PY_MB_bu[]    ={"��������������������"};
const char PY_MB_ca[]    ={"��"};
const char PY_MB_cai[]   ={"�²ŲĲƲòɲʲǲȲ˲�"};
const char PY_MB_can[]   ={"�βͲвϲѲҲ�"};
const char PY_MB_cang[]  ={"�ֲײԲղ�"};
const char PY_MB_cao[]   ={"�ٲڲܲ۲�"};
const char PY_MB_ce[]    ={"���޲��"};
const char PY_MB_ceng[]  ={"�����"};
const char PY_MB_cha[]   ={"������������ɲ"};
const char PY_MB_chai[]  ={"����"};
const char PY_MB_chan[]  ={"�������������������"};
const char PY_MB_chang[] ={"������������������������"};
const char PY_MB_chao[]  ={"��������������������"};
const char PY_MB_che[]   ={"������������"};
const char PY_MB_chen[]  ={"�������������³��ĳ�"};
const char PY_MB_cheng[] ={"�Ƴųɳʳгϳǳ˳ͳ̳γȳѳҳ�"};
const char PY_MB_chi[]   ={"�Գճڳس۳ٳֳ߳޳ݳܳ����"};
const char PY_MB_chong[] ={"������"};
const char PY_MB_chou[]  ={"�������������"};
const char PY_MB_chu[]   ={"����������������������������������"};
const char PY_MB_chuai[] ={"��"};
const char PY_MB_chuan[] ={"��������������"};
const char PY_MB_chuang[]={"����������"};
const char PY_MB_chui[]  ={"����������"};
const char PY_MB_chun[]  ={"��������������"};
const char PY_MB_chuo[]  ={"��"};
const char PY_MB_ci[]    ={"�ôʴĴɴȴǴŴƴ˴δ̴�"};
const char PY_MB_cong[]  ={"�ѴӴҴдϴ�"};
const char PY_MB_cou[]   ={"��"};
const char PY_MB_cu[]    ={"�ִٴ״�"};
const char PY_MB_cuan[]  ={"�ڴܴ�"};
const char PY_MB_cui[]   ={"�޴ߴݴ�����"};
const char PY_MB_cun[]   ={"����"};
const char PY_MB_cuo[]   ={"�������"};
const char PY_MB_da[]    ={"�������"};
const char PY_MB_dai[]   ={"������������������������"};
const char PY_MB_dan[]   ={"������������������������������"};
const char PY_MB_dang[]  ={"����������"};
const char PY_MB_dao[]   ={"������������������������"};
const char PY_MB_de[]    ={"�õµ�"};
const char PY_MB_deng[]  ={"�Ƶǵŵȵ˵ʵ�"};
const char PY_MB_di[]    ={"�͵̵εҵϵеӵѵյ׵ֵصܵ۵ݵڵ޵�"};
const char PY_MB_dian[]  ={"���ߵ�������������"};
const char PY_MB_diao[]  ={"�����������"};
const char PY_MB_die[]   ={"��������������"};
const char PY_MB_ding[]  ={"������������������"};
const char PY_MB_diu[]   ={"��"};
const char PY_MB_dong[]  ={"��������������������"};
const char PY_MB_dou[]   ={"����������������"};
const char PY_MB_du[]    ={"�����������¶ĶöʶŶǶȶɶ�"};
const char PY_MB_duan[]  ={"�˶̶ζ϶ж�"};
const char PY_MB_dui[]   ={"�ѶӶԶ�"};
const char PY_MB_dun[]   ={"�ֶضն׶ܶ۶ٶ�"};
const char PY_MB_duo[]   ={"��߶�޶��������"};
const char PY_MB_e[]     ={"����������������"};
const char PY_MB_en[]    ={"��"};
const char PY_MB_er[]    ={"����������������"};
const char PY_MB_fa[]    ={"����������������"};
const char PY_MB_fan[]   ={"����������������������������������"};
const char PY_MB_fang[]  ={"���������������·÷ķ�"};
const char PY_MB_fei[]   ={"�ɷǷȷƷʷ˷̷ͷϷзη�"};
const char PY_MB_fen[]   ={"�ַԷ׷ҷշӷطڷٷ۷ݷܷ޷߷�"};
const char PY_MB_feng[]  ={"����������������"};
const char PY_MB_fo[]    ={"��"};
const char PY_MB_fou[]   ={"��"};
const char PY_MB_fu[]    ={"������󸥷�����������������������������������������������������������������������������"};
const char PY_MB_ga[]    ={"�¸�"};
const char PY_MB_gai[]   ={"�øĸƸǸȸ�"};
const char PY_MB_gan[]   ={"�ɸʸ˸θ̸͸ѸϸҸи�"};
const char PY_MB_gang[]  ={"�Ըոڸٸظ׸ָ۸�"};
const char PY_MB_gao[]   ={"�޸�߸�ݸ�����"};
const char PY_MB_ge[]    ={"����������������������"};
const char PY_MB_gei[]   ={"��"};
const char PY_MB_gen[]   ={"����"};
const char PY_MB_geng[]  ={"��������������"};
const char PY_MB_gong[]  ={"������������������������������"};
const char PY_MB_gou[]   ={"������������������"};
const char PY_MB_gu[]    ={"�����ù¹��������ŹȹɹǹƹĹ̹ʹ˹�"};
const char PY_MB_gua[]   ={"�Ϲιйѹҹ�"};
const char PY_MB_guai[]  ={"�Թչ�"};
const char PY_MB_guan[]  ={"�ع۹ٹڹ׹ݹܹ�߹��"};
const char PY_MB_guang[] ={"����"};
const char PY_MB_gui[]   ={"������������������"};
const char PY_MB_gun[]   ={"������"};
const char PY_MB_guo[]   ={"������������"};
const char PY_MB_ha[]    ={"���"};
const char PY_MB_hai[]   ={"��������������"};
const char PY_MB_han[]   ={"��������������������������������������"};
const char PY_MB_hang[]  ={"������"};
const char PY_MB_hao[]   ={"���������úºźƺ�"};
const char PY_MB_he[]    ={"�ǺȺ̺ϺκͺӺҺ˺ɺԺкʺغֺպ�"};
const char PY_MB_hei[]   ={"�ں�"};
const char PY_MB_hen[]   ={"�ۺܺݺ�"};
const char PY_MB_heng[]  ={"��ߺ���"};
const char PY_MB_hong[]  ={"����������"};
const char PY_MB_hou[]   ={"��������"};
const char PY_MB_hu[]    ={"������������������������������������"};
const char PY_MB_hua[]   ={"������������������"};
const char PY_MB_huai[]  ={"����������"};
const char PY_MB_huan[]  ={"�����������û»�������������"};
const char PY_MB_huang[] ={"�ĻŻʻ˻ƻ̻ͻȻǻɻлλѻ�"};
const char PY_MB_hui[]   ={"�һֻӻԻջػ׻ڻܻ������߻޻�ݻٻ�"};
const char PY_MB_hun[]   ={"�������"};
const char PY_MB_huo[]   ={"�������������"};
const char PY_MB_ji[]    ={"���������������������������������������������������������������������ƼǼ��ͼ˼ɼ��ʼ����ȼü̼żļ¼�������"};
const char PY_MB_jia[]   ={"�ӼмѼϼҼμԼռ׼ּؼۼݼܼټ޼�Ю"};
const char PY_MB_jian[]  ={"����߼����������������������������������������������������"};
const char PY_MB_jiang[] ={"��������������������������"};
const char PY_MB_jiao[]  ={"���������������������ǽƽʽȽýŽ½��˽ɽнνϽ̽ѽ;���"};
const char PY_MB_jie[]   ={"�׽Խӽսҽֽڽٽܽ��ݽ޽ؽ߽����������"};
const char PY_MB_jin[]   ={"���������������������������������"};
const char PY_MB_jing[]  ={"��������������������������������������������������"};
const char PY_MB_jiong[] ={"����"};
const char PY_MB_jiu[]   ={"�������žþľ��¾ƾɾʾ̾ξǾȾ;�"};
const char PY_MB_ju[]    ={"�ӾоѾԾҾϾֽ۾վ׾ھپؾ�޾ܾ߾����ݾ��۾�"};
const char PY_MB_juan[]  ={"��������"};
const char PY_MB_jue[]   ={"��������������"};
const char PY_MB_jun[]   ={"����������������������"};
const char PY_MB_ka[]    ={"������"};
const char PY_MB_kai[]   ={"����������"};
const char PY_MB_kan[]   ={"��������������"};
const char PY_MB_kang[]  ={"��������������"};
const char PY_MB_kao[]   ={"��������"};
const char PY_MB_ke[]    ={"�����¿ƿÿſĿǿȿɿʿ˿̿Ϳ�"};
const char PY_MB_ken[]   ={"�Ͽѿҿ�"};
const char PY_MB_keng[]  ={"�Կ�"};
const char PY_MB_kong[]  ={"�տ׿ֿ�"};
const char PY_MB_kou[]   ={"�ٿڿۿ�"};
const char PY_MB_ku[]    ={"�ݿ޿߿����"};
const char PY_MB_kua[]   ={"������"};
const char PY_MB_kuai[]  ={"�����"};
const char PY_MB_kuan[]  ={"���"};
const char PY_MB_kuang[] ={"�����������"};
const char PY_MB_kui[]   ={"����������������������"};
const char PY_MB_kun[]   ={"��������"};
const char PY_MB_kuo[]   ={"��������"};
const char PY_MB_la[]    ={"��������������"};
const char PY_MB_lai[]   ={"������"};
const char PY_MB_lan[]   ={"������������������������������"};
const char PY_MB_lang[]  ={"��������������"};
const char PY_MB_lao[]   ={"������������������"};
const char PY_MB_le[]    ={"������"};
const char PY_MB_lei[]   ={"����������������������"};
const char PY_MB_leng[]  ={"������"};
const char PY_MB_li[]    ={"��������������������������������������������������������������������"};
const char PY_MB_lian[]  ={"����������������������������"};
const char PY_MB_liang[] ={"������������������������"};
const char PY_MB_liao[]  ={"������������������������"};
const char PY_MB_lie[]   ={"����������"};
const char PY_MB_lin[]   ={"������������������������"};
const char PY_MB_ling[]  ={"����������������������������"};
const char PY_MB_liu[]   ={"����������������������"};
const char PY_MB_long[]  ={"��������¡��¤¢£"};
const char PY_MB_lou[]   ={"¦¥§¨ª©"};
const char PY_MB_lu[]    ={"¶¬®«¯­±²°³½¼¸¹»µ·¾º´"};
const char PY_MB_luan[]  ={"������������"};
const char PY_MB_lue[]   ={"����"};
const char PY_MB_lun[]   ={"��������������"};
const char PY_MB_luo[]   ={"������������������������"};
const char PY_MB_lv[]    ={"��¿������������������������"};
const char PY_MB_ma[]    ={"������������������"};
const char PY_MB_mai[]   ={"������������"};
const char PY_MB_man[]   ={"����������á������"};
const char PY_MB_mang[]  ={"æâäãçå"};
const char PY_MB_mao[]   ={"èëìéêîíïðóñò"};
const char PY_MB_me[]    ={"ô"};
const char PY_MB_mei[]   ={"ûöõü÷ýúøùÿ��þ��������"};
const char PY_MB_men[]   ={"������"};
const char PY_MB_meng[]  ={"����������������"};
const char PY_MB_mi[]    ={"����������������������������"};
const char PY_MB_mian[]  ={"������������������"};
const char PY_MB_miao[]  ={"����������������"};
const char PY_MB_mie[]   ={"����"};
const char PY_MB_min[]   ={"������������"};
const char PY_MB_ming[]  ={"������������"};
const char PY_MB_miu[]   ={"��"};
const char PY_MB_mo[]    ={"����ġģĤĦĥĢħĨĩĭİĪįĮīĬ"};
const char PY_MB_mou[]   ={"Ĳıĳ"};
const char PY_MB_mu[]    ={"ĸĶĵķĴľĿ��ļĹĻ��Ľĺ��"};
const char PY_MB_na[]    ={"��������������"};
const char PY_MB_nai[]   ={"����������"};
const char PY_MB_nan[]   ={"������"};
const char PY_MB_nang[]  ={"��"};
const char PY_MB_nao[]   ={"����������"};
const char PY_MB_ne[]    ={"��"};
const char PY_MB_nei[]   ={"����"};
const char PY_MB_nen[]   ={"��"};
const char PY_MB_neng[]  ={"��"};
const char PY_MB_ni[]    ={"����������������������"};
const char PY_MB_nian[]  ={"��������������"};
const char PY_MB_niang[] ={"����"};
const char PY_MB_niao[]  ={"����"};
const char PY_MB_nie[]   ={"��������������"};
const char PY_MB_nin[]   ={"��"};
const char PY_MB_ning[]  ={"��š������Ţ"};
const char PY_MB_niu[]   ={"ţŤŦť"};
const char PY_MB_nong[]  ={"ũŨŧŪ"};
const char PY_MB_nu[]    ={"ūŬŭ"};
const char PY_MB_nuan[]  ={"ů"};
const char PY_MB_nue[]   ={"űŰ"};
const char PY_MB_nuo[]   ={"ŲŵųŴ"};
const char PY_MB_nv[]    ={"Ů"};
const char PY_MB_o[]     ={"Ŷ"};
const char PY_MB_ou[]    ={"ŷŹŸŻżźŽ"};
const char PY_MB_pa[]    ={"ſž����������"};
const char PY_MB_pai[]   ={"������������"};
const char PY_MB_pan[]   ={"����������������"};
const char PY_MB_pang[]  ={"����������"};
const char PY_MB_pao[]   ={"��������������"};
const char PY_MB_pei[]   ={"������������������"};
const char PY_MB_pen[]   ={"����"};
const char PY_MB_peng[]  ={"����������������������������"};
const char PY_MB_pi[]    ={"��������������Ƥ��ƣơ��ƢƥƦƨƧƩ"};
const char PY_MB_pian[]  ={"Ƭƫƪƭ"};
const char PY_MB_piao[]  ={"ƯƮưƱ"};
const char PY_MB_pie[]   ={"ƲƳ"};
const char PY_MB_pin[]   ={"ƴƶƵƷƸ"};
const char PY_MB_ping[]  ={"ƹƽ��ƾƺƻ��ƿƼ"};
const char PY_MB_po[]    ={"����������������"};
const char PY_MB_pou[]   ={"��"};
const char PY_MB_pu[]    ={"������������������������������"};
const char PY_MB_qi[]    ={"������������������������������������������������������������������������"};
const char PY_MB_qia[]   ={"��ǡǢ"};
const char PY_MB_qian[]  ={"ǧǪǤǨǥǣǦǫǩǰǮǯǬǱǭǳǲǴǷǵǶǸ"};
const char PY_MB_qiang[] ={"ǺǼǹǻǿǽǾ��"};
const char PY_MB_qiao[]  ={"������������������������������"};
const char PY_MB_qie[]   ={"����������"};
const char PY_MB_qin[]   ={"����������������������"};
const char PY_MB_qing[]  ={"��������������������������"};
const char PY_MB_qiong[] ={"����"};
const char PY_MB_qiu[]   ={"����������������"};
const char PY_MB_qu[]    ={"����������������ȡȢȣȥȤ"};
const char PY_MB_quan[]  ={"ȦȫȨȪȭȬȩȧȮȰȯ"};
const char PY_MB_que[]   ={"Ȳȱȳȴȸȷȵȶ"};
const char PY_MB_qun[]   ={"ȹȺ"};
const char PY_MB_ran[]   ={"ȻȼȽȾ"};
const char PY_MB_rang[]  ={"ȿ��������"};
const char PY_MB_rao[]   ={"������"};
const char PY_MB_re[]    ={"����"};
const char PY_MB_ren[]   ={"��������������������"};
const char PY_MB_reng[]  ={"����"};
const char PY_MB_ri[]    ={"��"};
const char PY_MB_rong[]  ={"��������������������"};
const char PY_MB_rou[]   ={"������"};
const char PY_MB_ru[]    ={"��������������������"};
const char PY_MB_ruan[]  ={"����"};
const char PY_MB_rui[]   ={"������"};
const char PY_MB_run[]   ={"����"};
const char PY_MB_ruo[]   ={"����"};
const char PY_MB_sa[]    ={"������"};
const char PY_MB_sai[]   ={"��������"};
const char PY_MB_san[]   ={"����ɡɢ"};
const char PY_MB_sang[]  ={"ɣɤɥ"};
const char PY_MB_sao[]   ={"ɦɧɨɩ"};
const char PY_MB_se[]    ={"ɫɬɪ"};
const char PY_MB_sen[]   ={"ɭ"};
const char PY_MB_seng[]  ={"ɮ"};
const char PY_MB_sha[]   ={"ɱɳɴɰɯɵɶɷ��"};
const char PY_MB_shai[]  ={"ɸɹ"};
const char PY_MB_shan[]  ={"ɽɾɼ��ɺɿ������ɻ������������դ"};
const char PY_MB_shang[] ={"����������������"};
const char PY_MB_shao[]  ={"����������������������"};
const char PY_MB_she[]   ={"������������������������"};
const char PY_MB_shen[]  ={"��������������������������������ʲ"};
const char PY_MB_sheng[] ={"��������ʤ����ʡʥʢʣ"};
const char PY_MB_shi[]   ={"��ʬʧʦʭʫʩʨʪʮʯʱʶʵʰʴʳʷʸʹʼʻʺʿ��������ʾʽ������������������������������������"};
const char PY_MB_shou[]  ={"��������������������"};
const char PY_MB_shu[]   ={"������������������������������������������������������ˡ����������"};
const char PY_MB_shua[]  ={"ˢˣ"};
const char PY_MB_shuai[] ={"˥ˤ˦˧"};
const char PY_MB_shuan[] ={"˩˨"};
const char PY_MB_shuang[]={"˫˪ˬ"};
const char PY_MB_shui[]  ={"˭ˮ˰˯"};
const char PY_MB_shun[]  ={"˱˳˴˲"};
const char PY_MB_shuo[]  ={"˵˸˷˶"};
const char PY_MB_si[]    ={"˿˾˽˼˹˻˺����������������"};
const char PY_MB_song[]  ={"����������������"};
const char PY_MB_sou[]   ={"��������"};
const char PY_MB_su[]    ={"����������������������"};
const char PY_MB_suan[]  ={"������"};
const char PY_MB_sui[]   ={"����������������������"};
const char PY_MB_sun[]   ={"������"};
const char PY_MB_suo[]   ={"����������������"};
const char PY_MB_ta[]    ={"����������̡̢̤̣"};
const char PY_MB_tai[]   ={"̨̧̥̦̫̭̬̩̪"};
const char PY_MB_tan[]   ={"̸̵̷̶̴̮̰̯̲̱̳̹̻̺̼̾̿̽"};
const char PY_MB_tang[]  ={"��������������������������"};
const char PY_MB_tao[]   ={"����������������������"};
const char PY_MB_te[]    ={"��"};
const char PY_MB_teng[]  ={"��������"};
const char PY_MB_ti[]    ={"������������������������������"};
const char PY_MB_tian[]  ={"����������������"};
const char PY_MB_tiao[]  ={"������������"};
const char PY_MB_tie[]   ={"������"};
const char PY_MB_ting[]  ={"��͡����ͤͥͣͦͧ͢"};
const char PY_MB_tong[]  ={"ͨͬͮͩͭͯͪͫͳͱͰͲʹ"};
const char PY_MB_tou[]   ={"͵ͷͶ͸"};
const char PY_MB_tu[]    ={"͹ͺͻͼͽͿ;��������"};
const char PY_MB_tuan[]  ={"����"};
const char PY_MB_tui[]   ={"������������"};
const char PY_MB_tun[]   ={"��������"};
const char PY_MB_tuo[]   ={"����������������������"};
const char PY_MB_wa[]    ={"��������������"};
const char PY_MB_wai[]   ={"����"};
const char PY_MB_wan[]   ={"����������������������������������"};
const char PY_MB_wang[]  ={"��������������������"};
const char PY_MB_wei[]   ={"Σ��΢ΡΪΤΧΥΦΨΩάΫΰαβγέίή��δλζηθξνιμεοκ"};
const char PY_MB_wen[]   ={"��������������������"};
const char PY_MB_weng[]  ={"������"};
const char PY_MB_wo[]    ={"������������������"};
const char PY_MB_wu[]    ={"����������������������������������������������������������"};
const char PY_MB_xi[]    ={"Ϧϫ����ϣ������Ϣ��Ϥϧϩ����ϬϡϪ��Ϩ����ϥϰϯϮϱϭϴϲϷϵϸ϶"};
const char PY_MB_xia[]   ={"ϺϹϻ��Ͽ��ϾϽϼ������"};
const char PY_MB_xian[]  ={"ϳ����������������������������������������������������"};
const char PY_MB_xiang[] ={"����������������������������������������"};
const char PY_MB_xiao[]  ={"����������������С��ТФ��ЧУЦХ"};
const char PY_MB_xie[]   ={"ЩШЪЫЭавбгЯЬдйкжмелиз"};
const char PY_MB_xin[]   ={"����о����п��н����"};
const char PY_MB_xing[]  ={"����������������������������"};
const char PY_MB_xiong[] ={"��������������"};
const char PY_MB_xiu[]   ={"��������������������"};
const char PY_MB_xu[]    ={"��������������������������������������"};
const char PY_MB_xuan[]  ={"������������ѡѢѤѣ"};
const char PY_MB_xue[]   ={"��ѥѦѨѧѩѪ"};
const char PY_MB_xun[]   ={"ѫѬѰѲѮѱѯѭѵѶѴѸѷѳ"};
const char PY_MB_ya[]    ={"ѾѹѽѺѻѼ��ѿ����������������"};
const char PY_MB_yan[]   ={"������������������������������������������������������������������"};
const char PY_MB_yang[]  ={"����������������������������������"};
const char PY_MB_yao[]   ={"��������ҢҦҤҥҡң��ҧҨҩҪҫԿ"};
const char PY_MB_ye[]    ={"ҬҭүҮҲұҰҵҶҷҳҹҴҺҸ"};
const char PY_MB_yi[]    ={"һ����ҽ��ҿҼҾ������������������������������������������������������������������������������������������"};
const char PY_MB_yin[]   ={"������������������������������ӡ"};
const char PY_MB_ying[]  ={"ӦӢӤӧӣӥӭӯӫӨөӪӬӮӱӰӳӲ"};
const char PY_MB_yo[]    ={"Ӵ"};
const char PY_MB_yong[]  ={"ӶӵӸӹӺӷ��ӽӾ��ӿ��Ӽӻ��"};
const char PY_MB_you[]   ={"����������������������������������������"};
const char PY_MB_yu[]    ={"����������������������������������������������������Ԧ����������ԡԤ������Ԣ��ԣ������ԥ"};
const char PY_MB_yuan[]  ={"ԩԧԨԪԱ԰ԫԭԲԬԮԵԴԳԯԶԷԹԺԸ"};
const char PY_MB_yue[]   ={"ԻԼ��������Ծ��Խ"};
const char PY_MB_yun[]   ={"������������������������"};
const char PY_MB_za[]    ={"������զ"};
const char PY_MB_zai[]   ={"����������������"};
const char PY_MB_zan[]   ={"��������"};
const char PY_MB_zang[]  ={"������"};
const char PY_MB_zao[]   ={"����������������������������"};
const char PY_MB_ze[]    ={"��������"};
const char PY_MB_zei[]   ={"��"};
const char PY_MB_zen[]   ={"��"};
const char PY_MB_zeng[]  ={"������"};
const char PY_MB_zha[]   ={"����������բագէթըե��"};
const char PY_MB_zhai[]  ={"իժլ��խծկ"};
const char PY_MB_zhan[]  ={"մձճղհնչյոշռսջվ��տպ"};
const char PY_MB_zhang[] ={"��������������������������������"};
const char PY_MB_zhao[]  ={"��������������������צ"};
const char PY_MB_zhe[]   ={"����������������������"};
const char PY_MB_zhen[]  ={"��������������������������������֡"};
const char PY_MB_zheng[] ={"��������������������֤֣��֢"};
const char PY_MB_zhi[]   ={"ְֱֲֳִֵֶַָֹֺֻּֽ֧֥֦֪֭֮֨֯֫֬֩��־������������ֿ������������������"};
const char PY_MB_zhong[] ={"����������������������"};
const char PY_MB_zhou[]  ={"����������������������������"};
const char PY_MB_zhu[]   ={"������������������������������ס��ע��פ��ף��������"};
const char PY_MB_zhua[]  ={"ץ"};
const char PY_MB_zhuai[] ={"ק"};
const char PY_MB_zhuan[] ={"רשת׫׭"};
const char PY_MB_zhuang[]={"ױׯ׮װ׳״��ײ"};
const char PY_MB_zhui[]  ={"׷׵׶׹׺׸"};
const char PY_MB_zhun[]  ={"׻׼"};
const char PY_MB_zhuo[]  ={"׿׾׽��������������"};
const char PY_MB_zi[]    ={"����������������������������"};
const char PY_MB_zong[]  ={"��������������"};
const char PY_MB_zou[]   ={"��������"};
const char PY_MB_zu[]    ={"����������������"};
const char PY_MB_zuan[]  ={"׬����"};
const char PY_MB_zui[]   ={"��������"};
const char PY_MB_zun[]   ={"����"};
const char PY_MB_zuo[]   ={"��������������"};
const char PY_MB_space[] ={""};
//ƴ�������Ľṹ������
struct PinYinPCB const PYRankTwoList_a[]={{"",PY_MB_a},
                                    {"i",PY_MB_ai},
                                    {"n",PY_MB_an},
                                    {"ng",PY_MB_ang},
                                    {"o",PY_MB_ao}};
struct PinYinPCB const PYRankTwoList_b[]={{"a",PY_MB_ba},
                                    {"ai",PY_MB_bai},
                                    {"an",PY_MB_ban},
                                    {"ang",PY_MB_bang},
                                    {"ao",PY_MB_bao},
                                    {"ei",PY_MB_bei},
                                    {"en",PY_MB_ben},
                                    {"eng",PY_MB_beng},
                                    {"i",PY_MB_bi},
                                    {"ian",PY_MB_bian},
                                    {"iao",PY_MB_biao},
                                    {"ie",PY_MB_bie},
                                    {"in",PY_MB_bin},
                                    {"ing",PY_MB_bing},
                                    {"o",PY_MB_bo},
                                    {"u",PY_MB_bu}};
struct PinYinPCB const PYRankTwoList_c[]={{"a",PY_MB_ca},
                                    {"ai",PY_MB_cai},
                                    {"an",PY_MB_can},
                                    {"ang",PY_MB_cang},
                                    {"ao",PY_MB_cao},
                                    {"e",PY_MB_ce},
                                    {"eng",PY_MB_ceng},
                                    {"ha",PY_MB_cha},
                                    {"hai",PY_MB_chai},
                                    {"han",PY_MB_chan},
                                    {"hang",PY_MB_chang},
                                    {"hao",PY_MB_chao},
                                    {"he",PY_MB_che},
                                    {"hen",PY_MB_chen},
                                    {"heng",PY_MB_cheng},
                                    {"hi",PY_MB_chi},
                                    {"hong",PY_MB_chong},
                                    {"hou",PY_MB_chou},
                                    {"hu",PY_MB_chu},
                                    {"huai",PY_MB_chuai},
                                    {"huan",PY_MB_chuan},
                                    {"huang",PY_MB_chuang},
                                    {"hui",PY_MB_chui},
                                    {"hun",PY_MB_chun},
                                    {"huo",PY_MB_chuo},
                                    {"i",PY_MB_ci},
                                    {"ong",PY_MB_cong},
                                    {"ou",PY_MB_cou},
                                    {"u",PY_MB_cu},
                                    {"uan",PY_MB_cuan},
                                    {"ui",PY_MB_cui},
                                    {"un",PY_MB_cun},
                                    {"uo",PY_MB_cuo}};
struct PinYinPCB const PYRankTwoList_d[]={{"a   ",PY_MB_da},
                                    {"ai",PY_MB_dai},
                                    {"an",PY_MB_dan},
                                    {"ang",PY_MB_dang},
                                    {"ao",PY_MB_dao},
                                    {"e",PY_MB_de},
                                    {"eng",PY_MB_deng},
                                    {"i",PY_MB_di},
                                    {"ian",PY_MB_dian},
                                    {"iao",PY_MB_diao},
                                    {"ie",PY_MB_die},
                                    {"ing",PY_MB_ding},
                                    {"iu",PY_MB_diu},
                                    {"ong",PY_MB_dong},
                                    {"ou",PY_MB_dou},
                                    {"u",PY_MB_du},
                                    {"uan",PY_MB_duan},
                                    {"ui",PY_MB_dui},
                                    {"un",PY_MB_dun},
                                    {"uo",PY_MB_duo}};
struct PinYinPCB const PYRankTwoList_e[]={{"",PY_MB_e},
                                    {"n",PY_MB_en},
                                    {"r",PY_MB_er}};
struct PinYinPCB const PYRankTwoList_f[]={{"a",PY_MB_fa},
                                    {"an",PY_MB_fan},
                                    {"ang",PY_MB_fang},
                                    {"ei",PY_MB_fei},
                                    {"en",PY_MB_fen},
                                    {"eng",PY_MB_feng},
                                    {"o",PY_MB_fo},
                                    {"ou",PY_MB_fou},
                                    {"u",PY_MB_fu}};
struct PinYinPCB const PYRankTwoList_g[]={{"a",PY_MB_ga},
                                    {"ai",PY_MB_gai},
                                    {"an",PY_MB_gan},
                                    {"ang",PY_MB_gang},
                                    {"ao",PY_MB_gao},
                                    {"e",PY_MB_ge},
                                    {"ei",PY_MB_gei},
                                    {"en",PY_MB_gan},
                                    {"eng",PY_MB_geng},
                                    {"ong",PY_MB_gong},
                                    {"ou",PY_MB_gou},
                                    {"u",PY_MB_gu},
                                    {"ua",PY_MB_gua},
                                    {"uai",PY_MB_guai},
                                    {"uan",PY_MB_guan},
                                    {"uang",PY_MB_guang},
                                    {"ui",PY_MB_gui},
                                    {"un",PY_MB_gun},
                                    {"uo",PY_MB_guo}};
struct PinYinPCB const PYRankTwoList_h[]={{"a",PY_MB_ha},
                                    {"ai",PY_MB_hai},
                                    {"an",PY_MB_han},
                                    {"ang",PY_MB_hang},
                                    {"ao",PY_MB_hao},
                                    {"e",PY_MB_he},
                                    {"ei",PY_MB_hei},
                                    {"en",PY_MB_hen},
                                    {"eng",PY_MB_heng},
                                    {"ong",PY_MB_hong},
                                    {"ou",PY_MB_hou},
                                    {"u",PY_MB_hu},
                                    {"ua",PY_MB_hua},
                                    {"uai",PY_MB_huai},
                                    {"uan",PY_MB_huan},
                                    {"uang ",PY_MB_huang},
                                    {"ui",PY_MB_hui},
                                    {"un",PY_MB_hun},
                                    {"uo",PY_MB_huo}};
struct PinYinPCB const PYRankTwoList_i[]={"",PY_MB_space};
struct PinYinPCB const PYRankTwoList_j[]={{"i",PY_MB_ji},
                                    {"ia",PY_MB_jia},
                                    {"ian",PY_MB_jian},
                                    {"iang",PY_MB_jiang},
                                    {"iao",PY_MB_jiao},
                                    {"ie",PY_MB_jie},
                                    {"in",PY_MB_jin},
                                    {"ing",PY_MB_jing},
                                    {"iong",PY_MB_jiong},
                                    {"iu",PY_MB_jiu},
                                    {"u",PY_MB_ju},
                                    {"uan",PY_MB_juan},
                                    {"ue",PY_MB_jue},
                                    {"un",PY_MB_jun}};
struct PinYinPCB const PYRankTwoList_k[]={{"a",PY_MB_ka},
                                    {"ai",PY_MB_kai},
                                    {"an",PY_MB_kan},
                                    {"ang",PY_MB_kang},
                                    {"ao",PY_MB_kao},
                                    {"e",PY_MB_ke},
                                    {"en",PY_MB_ken},
                                    {"eng",PY_MB_keng},
                                    {"ong",PY_MB_kong},
                                    {"ou",PY_MB_kou},
                                    {"u",PY_MB_ku},
                                    {"ua",PY_MB_kua},
                                    {"uai",PY_MB_kuai},
                                    {"uan",PY_MB_kuan},
                                    {"uang",PY_MB_kuang},
                                    {"ui",PY_MB_kui},
                                    {"un",PY_MB_kun},
                                    {"uo",PY_MB_kuo}};
struct PinYinPCB const PYRankTwoList_l[]={{"a",PY_MB_la},
                                    {"ai",PY_MB_lai},
                                    {"an",PY_MB_lan},
                                    {"ang",PY_MB_lang},
                                    {"ao",PY_MB_lao},
                                    {"e",PY_MB_le},
                                    {"ei",PY_MB_lei},
                                    {"eng",PY_MB_leng},
                                    {"i",PY_MB_li},
                                    {"ian",PY_MB_lian},
                                    {"iang",PY_MB_liang},
                                    {"iao",PY_MB_liao},
                                    {"ie",PY_MB_lie},
                                    {"in",PY_MB_lin},
                                    {"ing",PY_MB_ling},
                                    {"iu",PY_MB_liu},
                                    {"ong",PY_MB_long},
                                    {"ou",PY_MB_lou},
                                    {"u",PY_MB_lu},
                                    {"uan",PY_MB_luan},
                                    {"ue",PY_MB_lue},
                                    {"un",PY_MB_lun},
                                    {"uo",PY_MB_luo},
                                    {"v",PY_MB_lv}};
struct PinYinPCB const PYRankTwoList_m[]={{"a",PY_MB_ma},
                                    {"ai",PY_MB_mai},
                                    {"an",PY_MB_man},
                                    {"ang",PY_MB_mang},
                                    {"ao",PY_MB_mao},
                                    {"e",PY_MB_me},
                                    {"ei",PY_MB_mei},
                                    {"en",PY_MB_men},
                                    {"eng",PY_MB_meng},
                                    {"i",PY_MB_mi},
                                    {"ian",PY_MB_mian},
                                    {"iao",PY_MB_miao},
                                    {"ie",PY_MB_mie},
                                    {"in",PY_MB_min},
                                    {"ing",PY_MB_ming},
                                    {"iu",PY_MB_miu},
                                    {"o",PY_MB_mo},
                                    {"ou",PY_MB_mou},
                                    {"u",PY_MB_mu}};
struct PinYinPCB const PYRankTwoList_n[]={{"a",PY_MB_na},
                                    {"ai",PY_MB_nai},
                                    {"an",PY_MB_nan},
                                    {"ang",PY_MB_nang},
                                    {"ao",PY_MB_nao},
                                    {"e",PY_MB_ne},
                                    {"ei",PY_MB_nei},
                                    {"en",PY_MB_nen},
                                    {"eng",PY_MB_neng},
                                    {"i",PY_MB_ni},
                                    {"ian",PY_MB_nian},
                                    {"iang",PY_MB_niang},
                                    {"iao",PY_MB_niao},
                                    {"ie",PY_MB_nie},
                                    {"in",PY_MB_nin},
                                    {"ing",PY_MB_ning},
                                    {"iu",PY_MB_niu},
                                    {"ong",PY_MB_nong},
                                    {"u",PY_MB_nu},
                                    {"uan",PY_MB_nuan},
                                    {"ue",PY_MB_nue},
                                    {"uo",PY_MB_nuo},
                                    {"v",PY_MB_nv}};
struct PinYinPCB const PYRankTwoList_o[]={{"",PY_MB_o},
                                    {"u",PY_MB_ou}};
struct PinYinPCB const PYRankTwoList_p[]={{"a",PY_MB_pa},
                                    {"ai",PY_MB_pai},
                                    {"an",PY_MB_pan},
                                    {"ang",PY_MB_pang},
                                    {"ao",PY_MB_pao},
                                    {"ei",PY_MB_pei},
                                    {"en",PY_MB_pen},
                                    {"eng",PY_MB_peng},
                                    {"i",PY_MB_pi},
                                    {"ian",PY_MB_pian},
                                    {"iao",PY_MB_piao},
                                    {"ie",PY_MB_pie},
                                    {"in",PY_MB_pin},
                                    {"ing",PY_MB_ping},
                                    {"o",PY_MB_po},
                                    {"ou",PY_MB_pou},
                                    {"u",PY_MB_pu}};
struct PinYinPCB const PYRankTwoList_q[]={{"i",PY_MB_qi},
                                    {"ia",PY_MB_qia},
                                    {"ian",PY_MB_qian},
                                    {"iang",PY_MB_qiang},
                                    {"iao",PY_MB_qiao},
                                    {"ie",PY_MB_qie},
                                    {"in",PY_MB_qin},
                                    {"ing",PY_MB_qing},
                                    {"iong",PY_MB_qiong},
                                    {"iu",PY_MB_qiu},
                                    {"u",PY_MB_qu},
                                    {"uan",PY_MB_quan},
                                    {"ue",PY_MB_que},
                                    {"un",PY_MB_qun}};
struct PinYinPCB const PYRankTwoList_r[]={{"an",PY_MB_ran},
                                    {"ang",PY_MB_rang},
                                    {"ao",PY_MB_rao},
                                    {"e",PY_MB_re},
                                    {"en",PY_MB_ren},
                                    {"eng",PY_MB_reng},
                                    {"i",PY_MB_ri},
                                    {"ong",PY_MB_rong},
                                    {"ou",PY_MB_rou},
                                    {"u",PY_MB_ru},
                                    {"uan",PY_MB_ruan},
                                    {"ui",PY_MB_rui},
                                    {"un",PY_MB_run},
                                    {"uo",PY_MB_ruo}};
struct PinYinPCB const PYRankTwoList_s[]={{"a",PY_MB_sa},
                                    {"ai",PY_MB_sai},
                                    {"an",PY_MB_san},
                                    {"ang",PY_MB_sang},
                                    {"ao",PY_MB_sao},
                                    {"e",PY_MB_se},
                                    {"en",PY_MB_sen},
                                    {"eng",PY_MB_seng},
                                    {"ha",PY_MB_sha},
                                    {"hai",PY_MB_shai},
                                    {"han",PY_MB_shan},
                                    {"hang ",PY_MB_shang},
                                    {"hao",PY_MB_shao},
                                    {"he",PY_MB_she},
                                    {"hen",PY_MB_shen},
                                    {"heng",PY_MB_sheng},
                                    {"hi",PY_MB_shi},
                                    {"hou",PY_MB_shou},
                                    {"hu",PY_MB_shu},
                                    {"hua",PY_MB_shua},
                                    {"huai",PY_MB_shuai},
                                    {"huan",PY_MB_shuan},
                                    {"huang",PY_MB_shuang},
                                    {"hui",PY_MB_shui},
                                    {"hun",PY_MB_shun},
                                    {"huo",PY_MB_shuo},
                                    {"i",PY_MB_si},
                                    {"ong",PY_MB_song},
                                    {"ou",PY_MB_sou},
                                    {"u",PY_MB_su},
                                    {"uan",PY_MB_suan},
                                    {"ui",PY_MB_sui},
                                    {"un",PY_MB_sun},
                                    {"uo",PY_MB_suo}};
struct PinYinPCB const PYRankTwoList_t[]={{"a",PY_MB_ta},
                                    {"ai",PY_MB_tai},
                                    {"an",PY_MB_tan},
                                    {"ang",PY_MB_tang},
                                    {"ao",PY_MB_tao},
                                    {"e",PY_MB_te},
                                    {"eng",PY_MB_teng},
                                    {"i",PY_MB_ti},
                                    {"ian",PY_MB_tian},
                                    {"iao",PY_MB_tiao},
                                    {"ie",PY_MB_tie},
                                    {"ing",PY_MB_ting},
                                    {"ong",PY_MB_tong},
                                    {"ou",PY_MB_tou},
                                    {"u",PY_MB_tu},
                                    {"uan",PY_MB_tuan},
                                    {"ui",PY_MB_tui},
                                    {"un",PY_MB_tun},
                                    {"uo",PY_MB_tuo}};
struct PinYinPCB const PYRankTwoList_u[]={{"",PY_MB_space}};
struct PinYinPCB const PYRankTwoList_v[]={{"",PY_MB_space}};
struct PinYinPCB const PYRankTwoList_w[]={{"a",PY_MB_wa},
                                    {"ai",PY_MB_wai},
                                    {"an",PY_MB_wan},
                                    {"ang",PY_MB_wang},
                                    {"ei",PY_MB_wei},
                                    {"en",PY_MB_wen},
                                    {"eng",PY_MB_weng},
                                    {"o",PY_MB_wo},
                                    {"u",PY_MB_wu}};
struct PinYinPCB const PYRankTwoList_x[]={{"i",PY_MB_xi},
                                    {"ia",PY_MB_xia},
                                    {"ian",PY_MB_xiao},
                                    {"iang",PY_MB_xiang},
                                    {"iao",PY_MB_xiao},
                                    {"ie",PY_MB_xie},
                                    {"in",PY_MB_xin},
                                    {"ing",PY_MB_xing},
                                    {"iong",PY_MB_xiong},
                                    {"iu",PY_MB_xiu},
                                    {"u",PY_MB_xu},
                                    {"uan",PY_MB_xuan},
                                    {"ue",PY_MB_xue},
                                    {"un",PY_MB_xun}};
struct PinYinPCB const PYRankTwoList_y[]={{"a",PY_MB_ya},
                                    {"an",PY_MB_yan},
                                    {"ang",PY_MB_yang},
                                    {"ao",PY_MB_yao},
                                    {"e",PY_MB_ye},
                                    {"i",PY_MB_yi},
                                    {"in",PY_MB_yin},
                                    {"ing",PY_MB_ying},
                                    {"o",PY_MB_yo},
                                    {"ong",PY_MB_yong},
                                    {"ou",PY_MB_you},
                                    {"u",PY_MB_yu},
                                    {"uan",PY_MB_yuan},
                                    {"ue",PY_MB_yue},
                                    {"un",PY_MB_yun}};
struct PinYinPCB const PYRankTwoList_z[]={{"a",PY_MB_za},
                                    {"ai",PY_MB_zai},
                                    {"an",PY_MB_zan},
                                    {"ang",PY_MB_zang},
                                    {"ao",PY_MB_zao},
                                    {"e",PY_MB_ze},
                                    {"ei",PY_MB_zei},
                                    {"en",PY_MB_zen},
                                    {"eng",PY_MB_zeng},
                                    {"ha",PY_MB_zha},
                                    {"hai",PY_MB_zhai},
                                    {"han",PY_MB_zhan},
                                    {"hang",PY_MB_zhang},
                                    {"hao",PY_MB_zhao},
                                    {"he",PY_MB_zhe},
                                    {"hen",PY_MB_zhen},
                                    {"heng",PY_MB_zheng},
                                    {"hi",PY_MB_zhi},
                                    {"hong",PY_MB_zhong},
                                    {"hou",PY_MB_zhou},
                                    {"hu",PY_MB_zhu},
                                    {"hua",PY_MB_zhua},
                                    {"huai",PY_MB_zhuai},
                                    {"huan",PY_MB_zhuan},
                                    {"huang",PY_MB_zhuang},
                                    {"hui",PY_MB_zhui},
                                    {"hun",PY_MB_zhun},
                                    {"huo",PY_MB_zhuo},
                                    {"i",PY_MB_zi},
                                    {"ong",PY_MB_zong},
                                    {"ou",PY_MB_zou},
                                    {"u",PY_MB_zu},
                                    {"uan",PY_MB_zuan},
                                    {"ui",PY_MB_zui},
                                    {"un",PY_MB_zun},
                                    {"uo",PY_MB_zuo}};
struct PinYinPCB const PYRankTwoList_end[]={"",PY_MB_space};
//ƴ�������Ľṹ�������ָ��
struct PinYinPCB const *PYRankThreeList[]={  PYRankTwoList_a,
                                            PYRankTwoList_b,
                                            PYRankTwoList_c,
                                            PYRankTwoList_d,
                                            PYRankTwoList_e,
                                            PYRankTwoList_f,
                                            PYRankTwoList_g,
                                            PYRankTwoList_h,
                                            PYRankTwoList_i,
                                            PYRankTwoList_j,
                                            PYRankTwoList_k,
                                            PYRankTwoList_l,
                                            PYRankTwoList_m,
                                            PYRankTwoList_n,
                                            PYRankTwoList_o,
                                            PYRankTwoList_p,
                                            PYRankTwoList_q,
                                            PYRankTwoList_r,
                                            PYRankTwoList_s,
                                            PYRankTwoList_t,
                                            PYRankTwoList_u,
                                            PYRankTwoList_v,
                                            PYRankTwoList_w,
                                            PYRankTwoList_x,
                                            PYRankTwoList_y,
                                            PYRankTwoList_z,
                                            PYRankTwoList_end
										};

/*******************************************************************************
* �ļ���	  	 : PYSearch
* ����	         : ����ƴ���ĺ���
* ����           : ����ƴ��������
* ���           : ��
* ����           : ������ƴ�����ں��������Ӧ�����ؼ������ĺ��ֵ�ָ�룬
				   ���û�У����ؿ�ָ��
*******************************************************************************/	
char *PYSearch(unsigned char *msg)
{
	unsigned char count=0;
	unsigned char i=0;
	struct PinYinPCB const *headpcb; 					//���确b'���Զ���Ϊ��b'��ͷ�����к���
	struct PinYinPCB const *tailpcb;					//��b'����һ����c'���Զ���Ϊ��c'��ͷ�����к���
												//ͨ����Ƚ��������ݵĴ�С���Եõ���b'�����е�Ԫ��+����
	while(msg[count]!=0)count++;				//���������ƴ�����ֽ���		
	for(i=0;i<count;i++)						//��������ƴ���Ƿ���Ϲ淶
	{
		if((msg[i]>='a')&&(msg[i]<='z')) 		//����������������Ч
		{
			continue;
		}
		else if((msg[i]>='A')&&(msg[i]<='Z'))	//����Ǵ�д��ͳһ���Сд
		{
		    msg[i]+=0x20;						
			continue;
		}									   	//��������ݷǷ�������
		else
		{
		    return '\0';
		}
	}
	if((*msg=='i')||(*msg=='u')||(*msg=='v')||(*msg=='\0'))	//��������ݷǷ�������
	{
	    return '\0';
	}
	tailpcb=PYRankThreeList[*msg-'a'];	 		//�Զ���Ϊ*msg��ͷ������ƴ������
	headpcb=PYRankThreeList[*msg-'a'+1];		//�Զ���Ϊ*msg+1��ͷ������ƴ������
	for(;tailpcb<headpcb;tailpcb++)
	{
	    for(i=0;i<count-1;i++)				    //��������ƴ��������ṹ���е�ƴ���Ƿ�һ��
		{	
			if(*((*tailpcb).PYSerList+i)!=msg[i+1])
			{
			    break;
			}
		}
		if(i==(count-1))	 					//һ�£����ָ��
		{
		    return (char *)(*tailpcb).PYRankOneList;
		}
		
	}
	return '\0';								//���߷��ؿյ�ָ��
}

	
	

	

