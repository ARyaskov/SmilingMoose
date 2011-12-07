/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.*;

/**
 * Класс линии жизни простого процесса
 * @author alexander
 */
public class UIRectLifeLine extends UILifeLine {

    /**
     * Конструктор с параметрами
     * @param x Координата по Х
     * @param y Координата по У
     * @param text Текст ЛЖ
     */
    public UIRectLifeLine(int x, int y, String text) {
        
        this.x = x;
        this.y = y;
        this.w = 120;
        this.h = 300;

        m_text = text;

        setBounds(x, y, w, h);
        this.m_isEdit = false;
        this.m_isSelected = false;

        SceneItemListener listener = new SceneItemListener(this);

        this.addMouseListener(listener);
        this.addMouseMotionListener(listener);
        this.setToolTipText("Линия жизни: " + m_text);
    }

    
    @Override
    public void paint(Graphics g) {
        
        Graphics2D g2 = (Graphics2D)g;
        g2.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_LCD_HRGB);
        g2.setRenderingHint(RenderingHints.KEY_ALPHA_INTERPOLATION, RenderingHints.VALUE_ALPHA_INTERPOLATION_QUALITY);
        g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BICUBIC);

        Polygon dark = new Polygon();   // Полигон тени

        this.setBounds(this.x,this.y,w+10,h+10);

        // Смещаем координаты
        x+=10;
        y+=10;

        // Рисуем полигон
        dark.addPoint(x, y);
        dark.addPoint(x + 120, y);
        dark.addPoint(x + 120, y + 50);
        dark.addPoint(x, y + 50);

        // Возвращаем координаты обратно
        x-=10;
        y-=10;

        Color c = new Color(0, 0, 0,125);   // Цвет черный и прозрачный
        Stroke stroke = new BasicStroke(1);
        g2.setStroke(stroke);
        g.setColor(c);                      // Задаем цвет
        g.fillPolygon(dark);                // Заполняем полигон
        
//        g2.setStroke(new BasicStroke(3.0f,BasicStroke.CAP_BUTT,BasicStroke.JOIN_BEVEL,
//                1.0f,new float[]{8.0f,6.0f},0.0f));
//        g2.drawLine(68, 60, 68, 280);

        
        
        g2.setStroke(new BasicStroke(1));
        Polygon p = new Polygon();          // Полигон комментария

        // Рисуем прямоугольник со скошенным уголком
        p.addPoint(x, y);
        p.addPoint(x + 120, y);
        p.addPoint(x + 120, y + 50);
        p.addPoint(x, y + 50);

        if (m_isSelected)   // Если выбрали - заливаем желтым
            g.setColor(Color.getHSBColor(105, 215, 245));
        else                // Иначе, заливаем полигон голубоватым цветом
            g.setColor(Color.getHSBColor(205, 235, 245));

        g.fillPolygon(p);

        if (m_isSelected)   // Рисуем границы полигона красным цветом
            g.setColor(Color.red);
        else                // Рисуем границы полигона черным цветом
            g.setColor(Color.black);

        g.drawPolygon(p);
       
        g2.setStroke(new BasicStroke(1.0f,BasicStroke.CAP_BUTT,BasicStroke.JOIN_BEVEL,
                1.0f,new float[]{8.0f,4.0f},0.0f));
        g2.drawLine(60, 50, 60, 300);
 
         // Разбиваем текст на массив символов
        char [] drawedText = m_text.toCharArray();
        char [] dots = {'.','.','.'};
        
        g.drawChars(drawedText, 0, java.lang.Math.min(13, m_text.length()), x+5, y+15);
        
        if (m_text.length() >= 14)
            g.drawChars(dots, 0, 3, x+105, y+15);
            
        if (m_isEdit) 
            f.repaint();
        
    }
    
}
