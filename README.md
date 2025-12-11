Console Gomoku - An Algorithmic Approach in C++
Đây là dự án phần mềm đầu tay của tôi trong năm học thứ nhất tại Trường Đại học Công nghệ Thông tin (UIT) - ĐHQG TP.HCM. Dự án không chỉ dừng lại ở việc tái hiện trò chơi Cờ Caro (Gomoku) kinh điển, mà còn là một nỗ lực nghiêm túc nhằm ứng dụng các kiến thức nền tảng về Khoa học máy tính, đặc biệt là kỹ thuật quản lý bộ nhớ và tư duy thuật toán Heuristic.

Mục tiêu cốt lõi của dự án là trả lời câu hỏi: Làm thế nào để máy tính "hiểu" được một bàn cờ và đưa ra quyết định thông minh dựa trên các phép toán số học cơ bản?

Điểm nhấn kỹ thuật
Dự án tập trung vào các kỹ thuật lập trình cốt lõi, thể hiện tư duy tối ưu hóa của một sinh viên kỹ thuật:

1. Quản lý bộ nhớ thủ công (Manual Memory Management): Thay vì sử dụng các cấu trúc dữ liệu tự động như std::vector, tôi sử dụng con trỏ cấp 2 (char**) và các toán tử new/delete để quản lý bàn cờ. Điều này cho phép người chơi tùy chỉnh kích thước bàn cờ (từ 3x3 đến 20x20) mà chương trình vẫn đảm bảo không gian nhớ được cấp phát và thu hồi chính xác, tránh tuyệt đối lỗi rò rỉ bộ nhớ .

2. Nạp chồng toán tử (Operator Overloading): Để code trở nên trong sáng và mang tính trừu tượng hóa cao, tôi đã áp dụng kỹ thuật Nạp chồng toán tử cho các cấu trúc dữ liệu (struct). Việc cho phép các struct tự so sánh (operator<) và tự cộng gộp (operator+) giúp thuật toán sắp xếp và tính điểm trở nên tự nhiên hơn, đặt nền móng cho tư duy Lập trình hướng đối tượng.

3. Thuật toán Heuristic: AI của trò chơi không đánh ngẫu nhiên. Nó hoạt động dựa trên hàm đánh giá cục bộ (Local Evaluation Function). Bot có khả năng:

-Phân tích trạng thái bàn cờ hiện tại.

-Nhận diện các mẫu cờ nguy hiểm (chuỗi 3, chuỗi 4).

-Phân biệt rõ ràng giữa một chuỗi tấn công tiềm năng và một chuỗi đã bị chặn.

-Sử dụng thuật toán sắp xếp để ưu tiên các nước đi tối ưu nhất trong danh sách các nước đi khả dĩ.

Cơ chế hoạt động của Bot
Bot được thiết kế dựa trên tư duy "Tham lam" có chọn lọc. Tại mỗi lượt đi, Bot sẽ giả định đặt quân vào các ô trống xung quanh những nước đi cũ và tính toán điểm số dựa trên 4 hướng (Ngang, Dọc, Chéo chính, Chéo phụ).

Hệ thống điểm số được thiết kế để ưu tiên tuyệt đối việc phòng thủ khi đối phương sắp thắng (chặn chuỗi 4), đồng thời biết cách tấn công khi có cơ hội tạo ra chuỗi liên tiếp không bị chặn.

Hướng dẫn cài đặt và trải nghiệm
Dự án được viết bằng C++ chuẩn (Standard C++), không phụ thuộc vào thư viện bên ngoài (No external dependencies). Bạn có thể biên dịch mã nguồn bằng bất kỳ trình biên dịch C++ nào (GCC, Clang, MSVC).

Clone repository này về máy.

Mở project bằng Visual Studio hoặc biên dịch trực tiếp file .cpp.

Chạy chương trình và lựa chọn chế độ chơi (PvP hoặc PvE).

Lời kết và Hướng phát triển
Là dự án đầu tay, chương trình chắc chắn không tránh khỏi những hạn chế. Hiện tại, thuật toán Greedy của Bot chưa thể nhìn xa nhiều nước đi như thuật toán Minimax hay Alpha-Beta Pruning.

Tuy nhiên, việc hoàn thành dự án này là một cột mốc quan trọng, đánh dấu sự chuyển biến từ việc học lý thuyết sang thực hành tạo ra sản phẩm thực tế. Trong tương lai, tôi dự định sẽ nâng cấp trí tuệ nhân tạo của Bot và có thể tích hợp giao diện đồ họa (GUI) để tăng trải nghiệm người dùng.

Mọi ý kiến đóng góp đều được trân trọng để tôi có thể hoàn thiện hơn kỹ năng lập trình của mình.

Công Danh - Sinh viên Khoa Kỹ thuật Máy tính Trường Đại học Công nghệ Thông tin - ĐHQG TP.HCM
