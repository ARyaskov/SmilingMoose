package bbj.graphicsobjects;

import bbj.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

/** Класс, создающий т.н. селекторы - элементы интерфейса,
 * реализующие концепцию карусельного меню.
 * 
 * 
 * @author Lemon
 */
public class UISelector extends SceneItem {

    private Image m_arrowLeft;
    private Image m_arrowRight;
    private Image m_arrowRightInvert;
    private Image m_arrowLeftInvert;
    private Image m_leftSmall;
    private Image m_rightSmall;
    private Image m_centerBig;
    private boolean m_drawInvertLeft;
    private boolean m_drawInvertRight;
    private boolean m_drawSelect;
    private boolean m_drawSelectFill;
    private ArrayList<UIElementInfo> m_listOfUI;
    private ArrayList<Image> m_images24px;
    private ArrayList<Image> m_images48px;
    private ArrayList<String> m_orderOfTypes;
    private int m_pointer;
    private final int SMALL = 1;
    private final int BIG = 2;
    private final int SMALL2 = 3;
    private final int SHIFTL = 1;
    private final int SHIFTR = 2;

    public class UIElementInfo {

        public int m_height;
        public int m_width;
        public int m_x;
        public int m_y;
        public String m_name = "NULL";

        public UIElementInfo(int width, int height, int x, int y) {

            m_height = height;
            m_width = width;
            m_x = x;
            m_y = y;
        }

        public UIElementInfo(int width, int height, int x, int y, String name) {

            m_height = height;
            m_width = width;
            m_x = x;
            m_y = y;
            m_name = name;
        }
    }
    
   

    /**
     * 
     * @param nameOfItems Массив с названиями элементов карусельного меню
     * @param pointer Указатель - с какого элемента массива начинать отображение
     * @param path48 Путь к папке с 48-пикселными иконками (включая последний '/')
     * @param path24 Путь к папке с 24-пикселными иконками (включая последний '/')
     * @param path16 Путь к папке с 16-пикселными иконками (включая последний '/')
     * @param nameSuffix Приставка для данного типа элементов 
     *                   (например, для сообщений - message)
     */
    public UISelector(ArrayList<String> nameOfItems,
            int pointer,
            String path48,
            String path24,
            String path16,
            String nameSuffix) {

        super();

        if (nameOfItems.size() < 3) {
            System.out.println("UISelector: Нужно больше элементов для выбора! (Минимум 3)");
        } else {
            
            m_listOfUI = new ArrayList<UIElementInfo>();
            m_images24px = new ArrayList<Image>();
            m_images48px = new ArrayList<Image>();
            m_orderOfTypes = nameOfItems;

            m_pointer = pointer;

            Iterator it48 = m_orderOfTypes.iterator();
            while (it48.hasNext()) {
                m_images48px.add(new ImageIcon(BBJ.class.getResource(path48 + nameSuffix + it48.next() + ".png")).getImage());
            }
            Iterator it24 = m_orderOfTypes.iterator();
            while (it24.hasNext()) {
                m_images24px.add(new ImageIcon(BBJ.class.getResource(path24 + nameSuffix + it24.next() + ".png")).getImage());
            }

            m_drawInvertRight = false;
            m_drawInvertLeft = false;
            m_drawSelect = false;
            m_drawSelectFill = false;
            m_arrowLeft =
                    new ImageIcon(BBJ.class.getResource(path16 + "arrowLeft.png")).getImage();
            m_arrowRight =
                    new ImageIcon(BBJ.class.getResource(path16 + "arrowRight.png")).getImage();

            m_arrowLeftInvert =
                    new ImageIcon(BBJ.class.getResource(path16 + "arrowLeftInvert.png")).getImage();
            m_arrowRightInvert =
                    new ImageIcon(BBJ.class.getResource(path16 + "arrowRightInvert.png")).getImage();


            m_leftSmall = getTrinityImage(this.SMALL);
            m_centerBig = getTrinityImage(this.BIG);
            m_rightSmall = getTrinityImage(this.SMALL2);

            setSize(new Dimension(m_leftSmall.getWidth(null) * 2 + m_centerBig.getWidth(null) + 24,
                    m_centerBig.getHeight(null) + m_arrowRight.getHeight(null) + 24));
            System.out.printf(" W:%d, H:%d ",getSize().width, getSize().height);
            int distance = 2;
            m_listOfUI.add(new UIElementInfo(m_leftSmall.getWidth(null),
                    m_leftSmall.getHeight(null), distance, 2, "Previous"));
            distance += m_leftSmall.getWidth(null) + 10;
            m_listOfUI.add(new UIElementInfo(m_centerBig.getWidth(null),
                    m_centerBig.getHeight(null), distance, 2, "Current"));
            distance += m_centerBig.getWidth(null) + 10;
            m_listOfUI.add(new UIElementInfo(m_rightSmall.getWidth(null),
                    m_leftSmall.getHeight(null), distance, 2, "Forward"));


            int distanceArrow1 = (int) (getSize().getWidth() / 2 - m_arrowLeft.getWidth(null) / 2 - 5);
            int distanceArrow2 = (int) (getSize().getWidth() / 2 + m_arrowLeft.getWidth(null) / 2);

            m_listOfUI.add(new UIElementInfo(m_arrowLeft.getWidth(null),
                    m_arrowLeft.getHeight(null), distanceArrow1, m_centerBig.getHeight(null) + 22,
                    "arrowLeft"));

            m_listOfUI.add(new UIElementInfo(m_arrowRight.getWidth(null),
                    m_arrowRight.getHeight(null), distanceArrow2, m_centerBig.getHeight(null) + 22,
                    "arrowRight"));


            this.addMouseListener(new MouseSlot());
        }
    }

    /** Возвращает требуемую иконку из троицы текущих
     * 
     * @param type SMALL BIG SMALL2 - какую из трёх иконок следует вернуть
     * @return Иконка
     */
    public final Image getTrinityImage(int type) {
        Image result = null;
        switch (type) {
            case SMALL: {
                if (m_pointer > 0) {
                    result = m_images24px.get(m_pointer - 1);
                } else {
                    result = m_images24px.get(m_orderOfTypes.size() - 1);
                }
            }
            break;
            case BIG: {
                result = m_images48px.get(m_pointer);
            }
            break;
            case SMALL2: {
                if (m_pointer < m_orderOfTypes.size() - 1) {
                    result = m_images24px.get(m_pointer + 1);
                } else {
                    result = m_images24px.get(0);
                }
            }
            break;

        }
        return result;
    }

    /** Сдвиг указателя текущего элемента вправо/влево.
     * Зачем это надо, почему бы просто не сделать инкремент/декремент?
     * Из-за необходимости реализации кольцевого списка.
     * 
     * 
     * @param type Тип: SHIFTL (влево), SHIFTR (вправо)
     */
    public void shiftPointer(int type) {
        if (type == SHIFTL && m_pointer > 0) {
            m_pointer--;
        } else if (type == SHIFTL) {
            m_pointer = m_orderOfTypes.size() - 1;
        }

        if (type == SHIFTR && m_pointer < m_orderOfTypes.size() - 1) {
            m_pointer++;
        } else if (type == SHIFTR) {
            m_pointer = 0;
        }

    }

    @Override
    public void paintComponent(Graphics g) {

        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D) g;
        g2.setColor(new Color(255, 255, 255, 255));
        g2.fillRect(0, 0, getWidth(), getHeight());
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        g2.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
        g2.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_LCD_HRGB);
        g2.setRenderingHint(RenderingHints.KEY_ALPHA_INTERPOLATION, RenderingHints.VALUE_ALPHA_INTERPOLATION_QUALITY);
        g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BICUBIC);


        g2.setColor(new Color(0, 0, 0, 255));
        g2.drawRoundRect(0, 0, getWidth() - 1, getHeight() - 1, 10, 10);
        //g2.drawRect(0, 0, getWidth() - 1, getHeight() -1);

        m_leftSmall = getTrinityImage(this.SMALL);
        m_centerBig = getTrinityImage(this.BIG);
        m_rightSmall = getTrinityImage(this.SMALL2);


        g2.setColor(new Color(0, 0, 0, 0));
        g2.fillRect(0, 0, getWidth(), getHeight());

        g2.drawImage(m_leftSmall, getElementByName("Previous").m_x, getElementByName("Previous").m_y, null);
        g2.drawImage(m_centerBig, getElementByName("Current").m_x, getElementByName("Previous").m_y, null);
        g2.drawImage(m_rightSmall, getElementByName("Forward").m_x, getElementByName("Previous").m_y, null);

        int dist = (int) (getSize().getWidth() / 2 - m_arrowLeft.getWidth(null) / 2 - 5);
        g2.setFont(BBJ.messageNameFont);
        g2.setColor(new Color(0, 0, 0, 255));
        g2.drawString(m_orderOfTypes.get(m_pointer), dist, m_centerBig.getHeight(null) + 16);



        if (m_drawInvertLeft) {
            g2.drawImage(m_arrowLeftInvert, getElementByName("arrowLeft").m_x,
                    getElementByName("arrowLeft").m_y, null);
        } else {
            g2.drawImage(m_arrowLeft, getElementByName("arrowLeft").m_x,
                    getElementByName("arrowLeft").m_y, null);
        }
        if (m_drawInvertRight) {
            g2.drawImage(m_arrowRightInvert, getElementByName("arrowRight").m_x,
                    getElementByName("arrowRight").m_y, null);
        } else {
            g2.drawImage(m_arrowRight, getElementByName("arrowRight").m_x,
                    getElementByName("arrowRight").m_y, null);
        }

        if (m_drawSelectFill) {
            g2.setColor(new Color(255, 255, 255, 128));
            UIElementInfo curElem = getElementByName("Current");

            g2.fillRoundRect(curElem.m_x, curElem.m_y + 2, curElem.m_width,
                    curElem.m_height, 10, 10);
            g2.setColor(new Color(0, 0, 0, 255));
            g2.drawRoundRect(curElem.m_x, curElem.m_y + 2, curElem.m_width,
                    curElem.m_height, 10, 10);
        }
        if (m_drawSelect) {

            UIElementInfo curElem = getElementByName("Current");

            g2.setColor(new Color(0, 0, 0, 255));
            g2.drawRoundRect(curElem.m_x, curElem.m_y + 2, curElem.m_width,
                    curElem.m_height, 10, 10);

            /* Вариант с линиями
            UIElementInfo curElem = getElementByName("messageCurrent");
            g.setColor(new Color(0,0,0,255));
            g.drawLine(curElem.m_x, curElem.m_y, curElem.m_x,
            curElem.m_y + curElem.m_height);
            
            g.drawLine(curElem.m_x + curElem.m_width, curElem.m_y, curElem.m_x,
            curElem.m_y + curElem.m_height);*/
        }


    }

    public UIElementInfo getElementByName(String s) {
        /*Iterator itr = m_listOfUI.iterator();
        UIElementInfo element;
        while (itr.hasNext()) {
            element = (UIElementInfo) itr.next();
            if (element.m_name == null ? s == null : element.m_name.equals(s)) {
                return element;
            }

        }*/
        UIElementInfo element;
        int size = m_listOfUI.size();
        for (int i=0;i<size;i++){
            element = m_listOfUI.get(i);
            if (element.m_name == null ? s == null : element.m_name.equals(s)) {
                return element;
            }
        }
        return null;
    }

    class MouseSlot implements MouseListener, MouseMotionListener {

        public void mouseClicked(MouseEvent e) {
        }

        public void mouseEntered(MouseEvent e) {
        }

        public void mouseExited(MouseEvent e) {
        }

        public void mousePressed(MouseEvent e) {
            if (e.getButton() == MouseEvent.BUTTON1) {
                String owner = getOwner(e.getPoint());
                if ("arrowLeft".equals(owner)) {
                    m_drawInvertLeft = true;
                    shiftPointer(SHIFTL);
                    repaint();
                } else if ("arrowRight".equals(owner)) {
                    m_drawInvertRight = true;
                    shiftPointer(SHIFTR);
                    repaint();
                } else if ("Current".equals(owner)) {
                    m_drawSelectFill = true;
                    repaint();
                }


            }

        }

        public void mouseReleased(MouseEvent e) {
            if (e.getButton() == MouseEvent.BUTTON1) {
                String owner = getOwner(e.getPoint());
                if ("arrowLeft".equals(owner) && m_drawInvertLeft == true) {
                    m_drawInvertLeft = false;
                    repaint();
                } else if ("arrowRight".equals(owner) && m_drawInvertRight == true) {
                    m_drawInvertRight = false;
                    repaint();
                } else {
                    m_drawSelectFill = false;
                    repaint();
                }
            }
        }

        public void mouseDragged(MouseEvent e) {
        }

        public void mouseMoved(MouseEvent e) {
        }
    }

    /** Определяет элемент, расположенный по данным координатам
     * 
     * @param p Координаты
     * @return Имя элемента, выбирается из массива, переданного ранее в конструктор
     */
    public String getOwner(Point p) {
        Iterator itr = m_listOfUI.iterator();
        while (itr.hasNext()) {
            UIElementInfo element = (UIElementInfo) itr.next();
            if (element.m_x < p.x && element.m_y < p.y
                    && (element.m_x + element.m_width) > p.x
                    && (element.m_y + element.m_height) > p.y) {
                return element.m_name;
            }
        }
        return null;
    }

    /** Возвращает имя элемента, расположенного в центре (текущего)
     *  Полагается на имена из массива, переданного ранее в конструктор
     * 
     * @return Имя выбранного элемента
     */
    public String getSelected() {
        return m_orderOfTypes.get(m_pointer);
    }
}
